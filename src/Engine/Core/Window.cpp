#include "Window.h"

namespace BansheeEngine {
    Window::Window(const String &title, const unsigned int width, const unsigned int height): m_Width{width}, m_Height{height}, m_WindowTitle{title} {
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

        m_WindowPtr = glfwCreateWindow(static_cast<int>(m_Width), static_cast<int>(m_Height), m_WindowTitle.c_str(), nullptr, nullptr);
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

    Window::~Window() {
        Logger::INFO("Destroying window");
        glfwDestroyWindow(m_WindowPtr);
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_WindowPtr);
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_WindowPtr);
    }

    // TODO: Change this
    WindowSize Window::GetSize() const {
        int width, height;
        glfwGetWindowSize(m_WindowPtr, &width, &height);
        return WindowSize{width, height};
    }

    // TODO: Change this as well
    float Window::GetAspect() const {
        return static_cast<float>(m_Width) / static_cast<float>(m_Height);
    }

    GLFWwindow *Window::GetWindowPtr() const {
        return m_WindowPtr;
    }
}
