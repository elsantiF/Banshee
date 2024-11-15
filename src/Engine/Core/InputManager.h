#pragma once

#include <map>
#include <utility>

class InputManager {
    inline static std::map<int, bool> m_Keys;
    inline static std::map<int, bool> m_MouseButtons;
    inline static std::pair<double, double> m_MousePosition;

    static void SetKeyPressed(int keycode, bool isPressed);
    static void SetMouseButtonPressed(int button, bool isPressed);
    static void SetMousePosition(double x, double y);

public:
    static bool IsKeyPressed(int keycode);
    static bool IsMouseButtonPressed(int button);

    static std::pair<float, float> GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();

    friend class Window;
};
