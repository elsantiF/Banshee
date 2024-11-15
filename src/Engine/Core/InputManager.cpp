#include "InputManager.h"

void InputManager::SetKeyPressed(const int keycode, const bool isPressed) {
    m_Keys[keycode] = isPressed;
}

void InputManager::SetMouseButtonPressed(const int button, const bool isPressed) {
    m_MouseButtons[button] = isPressed;
}

void InputManager::SetMousePosition(const double x, const double y) {
    m_MousePosition = std::make_pair(x, y);
}

bool InputManager::IsKeyPressed(const int keycode) {
    return m_Keys[keycode];
}

bool InputManager::IsMouseButtonPressed(const int button) {
    return m_MouseButtons[button];
}

std::pair<float, float> InputManager::GetMousePosition() {
    return m_MousePosition;
}

double InputManager::GetMouseX() {
    return m_MousePosition.first;
}

double InputManager::GetMouseY() {
    return m_MousePosition.second;
}
