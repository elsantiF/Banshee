#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Core.h"
#include "Graphics/Renderer.h" // This needs to be in this order
#include "Window.h"
#include "Graphics/Shader.h"
#include "Components/Model.h"
#include "Components/Camera.h"
#include "Assets/ModelLoader.h"

namespace BansheeEngine {
    // TODO: m_Shader, m_Model and m_Camera should be in the scene, not here
    class Application {
        inline static Application *m_Instance;
        UniquePtr<Window> m_Window;
        UniquePtr<Shader> m_Shader;
        Model m_Model;
        Camera m_Camera;
        double m_Delta = 0.0;
        double m_LastFrame = 0.0;

    public:
        Application();
        void Render();
        void Update(float delta);
        void Terminate() const;
        void RenderImGUI() const; // TODO: This should be in a separate class
    };
}
