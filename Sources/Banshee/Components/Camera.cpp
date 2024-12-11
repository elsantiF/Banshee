module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/vector_common.hpp>
#include <tracy/Tracy.hpp>

module Banshee.Components.Camera;

import Banshee.Core.InputManager;

namespace Banshee {
    Camera::Camera(const f32 fov, const f32 aspect, const f32 near, const f32 far) : m_Fov{fov}, m_Aspect{aspect}, m_Near{near}, m_Far{far} {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
    }

    void Camera::Update(const f64 delta) {
        ZoneScoped;
        // Position update
        const f32 positionSpeed = 10.0f * static_cast<f32>(delta);

        if (InputManager::IsKeyPressed(GLFW_KEY_W)) {
            m_Transform.Translate(m_Transform.Forward() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_S)) {
            m_Transform.Translate(-m_Transform.Forward() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_D)) {
            m_Transform.Translate(m_Transform.Right() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_A)) {
            m_Transform.Translate(-m_Transform.Right() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_Q)) {
            m_Transform.Translate(m_Transform.Up() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_E)) {
            m_Transform.Translate(-m_Transform.Up() * positionSpeed);
        }

        // Rotation update
        const f32 rotationSpeed = 35.0f * static_cast<f32>(delta);

        if (InputManager::IsKeyPressed(GLFW_KEY_DOWN)) {
            m_Transform.Rotate(glm::vec3(-rotationSpeed, 0.f, 0.f));
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_UP)) {
            m_Transform.Rotate(glm::vec3(rotationSpeed, 0.f, 0.f));
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_LEFT)) {
            m_Transform.Rotate(glm::vec3(0.f, rotationSpeed, 0.f));
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_RIGHT)) {
            m_Transform.Rotate(glm::vec3(0.f, -rotationSpeed, 0.f));
        }

        // TODO: Add this again
        // m_Transform.RotationX() = glm::fclamp(m_Transform.RotationX(), -89.0f, 89.0f);

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_ADD)) {
            m_Fov = m_Fov + 10.f * delta;
        }

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
            m_Fov = m_Fov - 10.f * delta;
        }

        m_Fov = glm::fclamp(m_Fov, 1.0f, 120.0f);
    }
}
