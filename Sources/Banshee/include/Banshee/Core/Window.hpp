#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <GLFW/glfw3.h>
#include "InputManager.hpp"

namespace Banshee {
    using WindowSize = Pair<f32, f32>;

    // TODO: Add a way to set the window to be resizable
    class Window {
        u32 m_Width = 0;
        u32 m_Height = 0;

        String m_WindowTitle;
        GLFWwindow *m_WindowPtr = nullptr;

    public:
        Window(const String &title, int unsigned width, int unsigned height);
        ~Window();
        [[nodiscard]] bool ShouldClose() const;
        void SwapBuffers() const;
        [[nodiscard]] WindowSize GetSize() const;
        [[nodiscard]] f32 GetAspect() const;
        [[nodiscard]] GLFWwindow *GetWindowPtr() const;
    };
}
