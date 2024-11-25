#include "Application.h"

namespace BansheeEngine {
    Application::Application(UniquePtr<Scene> scene) {
        s_Instance = this;
        Logger::PANIC(!glfwInit(), "Failed to initialize GLFW");

        m_Window = MakeUnique<Window>("GL Renderer", 1280, 720);

        Renderer::Init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindowPtr(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        m_ActualScene = std::move(scene);
        m_ActualScene->OnCreate();

        m_Framebuffer = MakeUnique<Framebuffer>(m_Window->GetSize().first, m_Window->GetSize().second, 24);
        Logger::INFO("Engine started");
    }

    void Application::Render() {
        while (!m_Window->ShouldClose()) {
            m_ActualScene->OnUpdate(m_Delta);

            // Framebuffer begin
            m_Framebuffer->Bind();
            glEnable(GL_DEPTH_TEST);
            Renderer::Clear();

            m_ActualScene->OnRender(m_Delta);

            m_Framebuffer->Unbind();
            glDisable(GL_DEPTH_TEST);
            // Framebuffer end

            // Framebuffer display
            Renderer::Clear();
            m_Framebuffer->Draw();

            m_Window->SwapBuffers();
            glfwPollEvents();

            const double currentFrame = glfwGetTime();
            m_Delta = currentFrame - m_LastFrame;
            m_LastFrame = currentFrame;
        }
    }

    Application::~Application() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        Logger::INFO("Engine closing");
        glfwTerminate();
    }
}
