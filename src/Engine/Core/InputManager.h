#pragma once

#include "Core.h"

namespace BansheeEngine {
    class InputManager {
        inline static Map<int, bool> m_Keys;
        inline static Map<int, bool> m_MouseButtons;
        inline static Pair<double, double> m_MousePosition;

        static void SetKeyPressed(int keycode, bool isPressed);
        static void SetMouseButtonPressed(int button, bool isPressed);
        static void SetMousePosition(double x, double y);

    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);

        static Pair<double, double> GetMousePosition();
        static double GetMouseX();
        static double GetMouseY();

        friend class Window;
    };
}
