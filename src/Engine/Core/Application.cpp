#include "Application.h"

namespace BansheeEngine {
    Application::Application(UniquePtr<Scene> scene) {
        Logger::PANIC(!glfwInit(), "Failed to initialize GLFW");

        m_Window = MakeUnique<Window>();
        m_Window->Create("GL Renderer", 1280, 720);

        Renderer::Init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindowPtr(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        m_ActualScene = std::move(scene);
        m_ActualScene->OnCreate();

        Logger::INFO("Engine started");

        m_Instance = this;
    }

    void Application::Render() {
        while (!m_Window->ShouldClose()) {
            m_ActualScene->OnUpdate(m_Delta);

            Renderer::Clear();

            m_ActualScene->OnRender(m_Delta);

            m_Window->SwapBuffers();
            glfwPollEvents();

            const double currentFrame = glfwGetTime();
            m_Delta = currentFrame - m_LastFrame;
            m_LastFrame = currentFrame;
        }

        Terminate();
    }

    void Application::Terminate() const {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        m_Window->Destroy();
        Logger::INFO("Engine closing");
        glfwTerminate();
    }
}
