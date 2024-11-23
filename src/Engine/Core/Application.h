#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Core.h"
#include "Graphics/Renderer.h" // This needs to be in this order
#include "Window.h"
#include "Scene.h"

namespace BansheeEngine {
    class Application {
        inline static Application *s_Instance = nullptr;
        UniquePtr<Scene> m_ActualScene;
        UniquePtr<Window> m_Window;

        double m_Delta = 0.0;
        double m_LastFrame = 0.0;

    public:
        explicit Application(UniquePtr<Scene> scene);
        void Render();
        void Terminate() const;
        UniquePtr<Window> &GetWindow() { return m_Window; }
        static Application *GetInstance() { return s_Instance; }
    };
}
