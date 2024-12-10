module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/vector_common.hpp>
#include <tracy/Tracy.hpp>

module Banshee.Components.Camera;

import Banshee.Core.InputManager;

namespace Banshee {
    Camera::Camera(const f32 fov, const f32 aspect, const f32 near, const f32 far)
        : m_Fov{fov}, m_Aspect{aspect}, m_Near{near}, m_Far{far} {

        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
        m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        UpdateCameraVectors();
    }

    void Camera::UpdateCameraVectors() {
        ZoneScoped;
        glm::vec3 front;

        const f32 radiansYaw = glm::radians(m_Transform.GetRotation().y);
        const f32 radiansPitch = glm::radians(m_Transform.GetRotation().x);

        front.x = cos(radiansYaw) * cos(radiansPitch);
        front.y = sin(radiansPitch);
        front.z = sin(radiansYaw) * cos(radiansPitch);

        m_Front = glm::normalize(front);
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }

    void Camera::Update(const f64 delta) {
        ZoneScoped;
        // Position update
        const f32 positionSpeed = 10.0f * static_cast<f32>(delta);

        if (InputManager::IsKeyPressed(GLFW_KEY_W)) {
            m_Transform.Translate(m_Front * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_S)) {
            m_Transform.Translate(-m_Front * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_D)) {
            m_Transform.Translate(m_Right * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_A)) {
            m_Transform.Translate(-m_Right * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_Q)) {
            m_Transform.Translate(m_Up * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_E)) {
            m_Transform.Translate(-m_Up * positionSpeed);
        }

        // Rotation update
        const f32 rotationSpeed = 35.0f * static_cast<f32>(delta);

        if (InputManager::IsKeyPressed(GLFW_KEY_DOWN)) {
            m_Transform.RotateX(-rotationSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_UP)) {
            m_Transform.RotateX(rotationSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_LEFT)) {
            m_Transform.RotateY(-rotationSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_RIGHT)) {
            m_Transform.RotateY(rotationSpeed);
        }

        m_Transform.GetRotationX() = glm::fclamp(m_Transform.GetRotationX(), -89.0f, 89.0f);

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_ADD)) {
            m_Fov = m_Fov + 0.1f;
        }

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
            m_Fov = m_Fov - 0.1f;
        }

        m_Fov = glm::fclamp(m_Fov, 1.0f, 120.0f);

        UpdateCameraVectors();
    }
}
