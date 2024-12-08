module;
#include <unordered_map>
#include <utility>

module Banshee.Core.InputManager;

namespace Banshee {
    void InputManager::SetKeyPressed(const int keycode, const bool isPressed) { m_Keys[keycode] = isPressed; }

    void InputManager::SetMouseButtonPressed(const int button, const bool isPressed) { m_MouseButtons[button] = isPressed; }

    void InputManager::SetMousePosition(const f64 x, const f64 y) { m_MousePosition = std::make_pair(x, y); }

    bool InputManager::IsKeyPressed(const int keycode) { return m_Keys[keycode]; }

    bool InputManager::IsMouseButtonPressed(const int button) { return m_MouseButtons[button]; }

    Pair<f64, f64> InputManager::GetMousePosition() { return m_MousePosition; }

    f64 InputManager::GetMouseX() { return m_MousePosition.first; }

    f64 InputManager::GetMouseY() { return m_MousePosition.second; }
}
