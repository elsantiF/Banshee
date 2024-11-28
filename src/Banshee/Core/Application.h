#pragma once

#include <glad/glad.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Core.h"
#include "Graphics/Renderer.h" // This needs to be in this order
#include "Graphics/Framebuffer.h"
#include "Window.h"
#include "Level.h"

namespace Banshee {
    class Application {
        inline static Application *s_Instance = nullptr;
        UniquePtr<Level> m_ActualLevel;
        UniquePtr<Window> m_Window;
        UniquePtr<Framebuffer> m_Framebuffer;

        bool m_Wireframe = false; // TODO: Move to Renderer when it's ready

        double m_Delta = 0.0;
        double m_LastFrame = 0.0;

    public:
        explicit Application(UniquePtr<Level> level);
        ~Application();
        void Render();
        UniquePtr<Window> &GetWindow();
        static Application *GetInstance();
        void SetWireframe(const bool wireframe); // TODO: Move to Renderer when it's ready
    };
}
