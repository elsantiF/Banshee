#include "Application.h"

Application::Application() {
    Logger::PANIC(!glfwInit(), "Failed to initialize GLFW");

    m_Window = std::make_unique<Window>();
    m_Window->Create("GL Renderer", 1280, 720);
    Logger::PANIC(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)), "Failed to initialize GLAD");

    //glViewport(0, 0, 1280, 720);
    glClearColor(0.3f, 0.0f, 0.3f, 0.0f);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_VERSION)));
    Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_VENDOR)));
    Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindowPtr(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    m_Camera = Camera(m_Window.get());
    m_Shader.Init("resources/shaders/basic");
    m_Model = ModelLoader::LoadModel("resources/models/backpack.obj");

    Logger::INFO("Engine started");

    m_Instance = this;
}

void Application::Render() {
    while (!m_Window->ShouldClose()) {
        Update(m_Delta);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_Shader.Bind();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_Shader.SetMat4Uniform("u_MatProjection",m_Camera.GetProjectionMatrix());
        m_Shader.SetMat4Uniform("u_MatView", m_Camera.GetViewMatrix());
        m_Shader.SetVec3Uniform("u_LightPosition", glm::vec3(1.2f, 1.0f, 2.0f));

        m_Model.Rotate({0.0f, 1.0, 0.0f}, glm::degrees(glfwGetTime()));;

        m_Model.Draw(m_Shader);

        RenderImGUI();

        m_Window->SwapBuffers();
        glfwPollEvents();

        const double currentFrame = glfwGetTime();
        m_Delta = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
    }

    Terminate();
}

void Application::Update(float delta) {
    m_Camera.Update(delta);
}

void Application::Terminate() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    m_Window->Destroy();
    Logger::INFO("Engine closing");
    glfwTerminate();
}

void Application::RenderImGUI() const {
    ImGui::Begin("Engine");

    ImGui::Text("Delta: %04f ms", m_Delta * 1000);

    ImGui::SeparatorText("Camera");
    glm::vec3 cameraPosition = m_Camera.GetCameraPosition();
    ImGui::Text("X: %04f Y: %04f Z: %04f", cameraPosition.x, cameraPosition.y, cameraPosition.z);

    ImGui::SeparatorText("Render");
    if (ImGui::Button("Solid render")) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (ImGui::Button("Wireframe render")) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
