#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <Spectre/Renderer/Renderer.hpp>
#include "Banshee/Core/Application.hpp"

#ifdef BE_OVER_9000
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

namespace Banshee {
    Application::Application() {
        s_Instance = this;
        Logger::PANIC(!glfwInit(), "Failed to initialize GLFW");

        m_Window = MakeScope<Window>("GL Renderer", 1280, 720);

        Spectre::Renderer::Init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindowPtr(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        m_LastFrame = glfwGetTime();
        Logger::INFO("Engine started");

        m_World = MakeScope<World>();
    }

    Application::~Application() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        m_Window.reset();
        Logger::INFO("Engine closing");
        glfwTerminate();
    }

    void Application::SetMainLevel(const Ref<Level> &level) const { m_World->SetLevel(level); }

    void Application::Render() {
        while (!m_Window->ShouldClose()) {
            PROFILE_SCOPE();
            m_World->Tick(m_Delta);
            m_World->Render();
            // Swap buffers
            PROFILE_FRAME_MARK();
            m_Window->SwapBuffers();
            PROFILE_GPU_COLLECT();
            glfwPollEvents();

            const f64 currentFrame = glfwGetTime();
            m_Delta = currentFrame - m_LastFrame;
            m_LastFrame = currentFrame;
        }
    }

    Scope<Window> &Application::GetWindow() { return m_Window; }

    Application *Application::GetInstance() { return s_Instance; }
}
