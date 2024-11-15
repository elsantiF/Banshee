#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Window.h"
#include "Graphics/Shader.h"
#include "Components/Model.h"
#include "Components/Camera.h"
#include "Assets/ModelLoader.h"

// TODO: m_Shader, m_Model and m_Camera should be in the scene, not here
class Application {
    inline static Application* m_Instance;
    std::unique_ptr<Window> m_Window = nullptr;
    Shader m_Shader;
    Model m_Model;
    Camera m_Camera;
    double m_Delta = 0.0;
    double m_LastFrame = 0.0;

public:
    Application();
    void Render();
    void Update(float delta);
    void Terminate() const;
    void RenderImGUI() const;       // TODO: This should be in a separate class
};
