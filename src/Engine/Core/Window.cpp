#include "Window.h"

void Window::Create(const std::string &title, const int width, const int height) {
    m_WindowTitle = title;
    m_Width = width;
    m_Height = height;

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_WindowPtr = glfwCreateWindow(m_Width, m_Height, m_WindowTitle.c_str(), nullptr, nullptr);
    Logger::PANIC(!m_WindowPtr, "Failed to create window");

    glfwMakeContextCurrent(m_WindowPtr);
    glfwSwapInterval(1);
    glfwShowWindow(m_WindowPtr);

    glfwSetKeyCallback(m_WindowPtr, [](GLFWwindow *window, const int key, int scancode, const int action, int mods) {
        if (action == GLFW_REPEAT) return;
        InputManager::SetKeyPressed(key, action == GLFW_PRESS);
    });

    glfwSetMouseButtonCallback(m_WindowPtr, [](GLFWwindow *window, const int button, const int action, int mods) {
        if (action == GLFW_REPEAT) return;
        InputManager::SetMouseButtonPressed(button, action == GLFW_PRESS);
    });

    glfwSetCursorPosCallback(m_WindowPtr, [](GLFWwindow *window, const double xpos, const double ypos) {
        InputManager::SetMousePosition(xpos, ypos);
    });

    Logger::INFO("Window created");
}

void Window::Destroy() const {
    Logger::INFO("Destroying window");
    glfwDestroyWindow(m_WindowPtr);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_WindowPtr);
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(m_WindowPtr);
}

WindowSize Window::GetSize() const {
    int width, height;
    glfwGetWindowSize(m_WindowPtr, &width, &height);
    return std::pair<float, float>{width, height};
}

float Window::GetAspect() const {
    return static_cast<float>(m_Width) / static_cast<float>(m_Height);
}

GLFWwindow *Window::GetWindowPtr() const {
    return m_WindowPtr;
}
