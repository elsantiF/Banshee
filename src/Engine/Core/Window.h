#pragma once

#include <GLFW/glfw3.h>

#include "Core.h"
#include "InputManager.h"

namespace BansheeEngine {
    using WindowSize = Pair<float, float>;

    // TODO: Add a way to set the window to be resizable
    class Window {
        int m_Width = 0;
        int m_Height = 0;

        String m_WindowTitle;
        GLFWwindow *m_WindowPtr = nullptr;

    public:
        void Create(const String &title, int width, int height);
        void Destroy() const;
        [[nodiscard]] bool ShouldClose() const;
        void SwapBuffers() const;
        [[nodiscard]] WindowSize GetSize() const;
        [[nodiscard]] float GetAspect() const;
        [[nodiscard]] GLFWwindow *GetWindowPtr() const;
    };
}
