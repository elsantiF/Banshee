#pragma once

#include <GLFW/glfw3.h>

#include "Core.h"
#include "InputManager.h"

namespace BansheeEngine {
    using WindowSize = std::pair<float, float>;

    class Window {
        int m_Width = 0;
        int m_Height = 0;

        std::string m_WindowTitle;
        GLFWwindow *m_WindowPtr = nullptr;

    public:
        void Create(const std::string &title, int width, int height);
        void Destroy() const;
        [[nodiscard]] bool ShouldClose() const;
        void SwapBuffers() const;
        [[nodiscard]] WindowSize GetSize() const;
        [[nodiscard]] float GetAspect() const;
        [[nodiscard]] GLFWwindow *GetWindowPtr() const;
    };
}
