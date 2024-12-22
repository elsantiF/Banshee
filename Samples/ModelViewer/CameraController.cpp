#include <Banshee/Core/InputManager.hpp>
#include <GLFW/glfw3.h>
#include "CameraController.h"

void CameraController::OnTick(const f64 delta) {
    PROFILE_SCOPE();
        const f32 translationSpeed = m_TranslationSpeed * static_cast<f32>(delta);
        const f32 rotationSpeed = m_RotationSpeed * static_cast<f32>(delta);

        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_W)) {
            m_Transform->Translate(m_Transform->Forward() * translationSpeed);
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_S)) {
            m_Transform->Translate(-m_Transform->Forward() * translationSpeed);
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_D)) {
            m_Transform->Translate(m_Transform->Right() * translationSpeed);
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_A)) {
            m_Transform->Translate(-m_Transform->Right() * translationSpeed);
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_Q)) {
            m_Transform->Translate(m_Transform->Up() * translationSpeed);
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_E)) {
            m_Transform->Translate(-m_Transform->Up() * translationSpeed);
        }

        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_DOWN)) {
            m_Transform->Rotate(glm::vec3(-rotationSpeed, 0.f, 0.f));
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_UP)) {
            m_Transform->Rotate(glm::vec3(rotationSpeed, 0.f, 0.f));
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_LEFT)) {
            m_Transform->Rotate(glm::vec3(0.f, rotationSpeed, 0.f));
        }
        if (Banshee::InputManager::IsKeyPressed(GLFW_KEY_RIGHT)) {
            m_Transform->Rotate(glm::vec3(0.f, -rotationSpeed, 0.f));
        }

        // TODO: Add this again
        // m_Transform.RotationX() = glm::fclamp(m_Transform.RotationX(), -89.0f, 89.0f);
        /*
        if (InputManager::IsKeyPressed(GLFW_KEY_KP_ADD)) {
            m_Camera->Fov() -= 10.f * delta;
        }

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
            m_Camera->Fov() += 10.f * delta;
        }

        m_Camera->Fov() = std::clamp(m_Camera->Fov(), 1.0f, 120.0f);
        */
}

void CameraController::OnImGui() {
    PROFILE_SCOPE();
    ImGui::SliderFloat("Translation Speed", &m_TranslationSpeed, 0.f, 100.f);
    ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.f, 100.f);
}