#include "Application.h"

#ifdef BE_OVER_9000
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

namespace Banshee {
    Application::Application(UniquePtr<Level> level) {
        s_Instance = this;
        Logger::PANIC(!glfwInit(), "Failed to initialize GLFW");

        m_Window = MakeUnique<Window>("GL Renderer", 1280, 720);

        Renderer::Init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindowPtr(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        m_ActualLevel = std::move(level);
        m_ActualLevel->OnCreate();

        m_Framebuffer = MakeUnique<Framebuffer>(m_Window->GetSize().first, m_Window->GetSize().second, 24);
        Logger::INFO("Engine started");
    }

    void Application::Render() {
        while (!m_Window->ShouldClose()) {
            m_ActualLevel->OnUpdate(m_Delta);

            // Framebuffer begin
            m_Framebuffer->Bind();
            glEnable(GL_DEPTH_TEST);
            Renderer::Clear();

            // Level rendering
            // TODO: Move to Renderer when it's ready, this is just a temporary solution
            if (m_Wireframe) {
                Renderer::SetPolygonMode(PolygonMode::LINE);
            } else {
                Renderer::SetPolygonMode(PolygonMode::FILL);
            }

            m_ActualLevel->OnRender(m_Delta);

            Renderer::SetPolygonMode(PolygonMode::FILL);

            m_Framebuffer->Unbind();
            glDisable(GL_DEPTH_TEST);

            // Framebuffer display
            Renderer::Clear();
            m_Framebuffer->Draw();

            // Render ImGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            m_ActualLevel->OnImGUI(m_Delta);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap buffers
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
