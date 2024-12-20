#pragma once

#include <Poltergeist/Poltergeist.hpp>

namespace Banshee {
    class InputManager {
        inline static UnorderedMap<int, bool> m_Keys;
        inline static UnorderedMap<int, bool> m_MouseButtons;
        inline static Pair<f64, f64> m_MousePosition;

    public:
        static void SetKeyPressed(int keycode, bool isPressed);
        static void SetMouseButtonPressed(int button, bool isPressed);
        static void SetMousePosition(f64 x, f64 y);

        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);

        static Pair<f64, f64> GetMousePosition();
        static f64 GetMouseX();
        static f64 GetMouseY();
    };
}
