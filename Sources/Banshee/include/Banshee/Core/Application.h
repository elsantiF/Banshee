#pragma once

#include <glad/glad.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Spectre/Renderer.h" // This needs to be in this order
#include "Spectre/Framebuffer.h"

#include "Banshee/Core/Core.h"
#include "Banshee/Core/Window.h"
#include "Banshee/Core/Level.h"

namespace Banshee {
    class Application {
        inline static Application *s_Instance = nullptr;
        UniquePtr<Level> m_ActualLevel;
        UniquePtr<Window> m_Window;

        f64 m_Delta = 0.0;
        f64 m_LastFrame = 0.0;

    public:
        explicit Application(UniquePtr<Level> level);
        ~Application();
        void Render();
        UniquePtr<Window> &GetWindow();
        static Application *GetInstance();
    };
}
