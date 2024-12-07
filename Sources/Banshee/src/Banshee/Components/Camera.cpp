#include "Banshee/Components/Camera.h"

namespace Banshee {
    Camera::Camera(const f32 fov, const f32 aspect, const f32 near, const f32 far)
        : m_Fov{fov}, m_Aspect{aspect}, m_Near{near}, m_Far{far}, m_Transform{} {

        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);

        m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
        m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        UpdateCameraVectors();
    }

    void Camera::UpdateCameraVectors() {
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

        // TODO: Add this again
        // if (m_Pitch > 89.0f) m_Pitch = 89.0f;
        // if (m_Pitch < -89.0f) m_Pitch = -89.0f;

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_ADD)) {
            const f32 fov = GetFov();
            if (fov < 179.9f) {
                SetFov(GetFov() + 0.1f);
            }
        }

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
            const f32 fov = GetFov();
            if (fov > 0.1f) {
                SetFov(GetFov() - 0.1f);
            }
        }

        UpdateCameraVectors();
    }

    f32 Camera::GetFov() const {
        return m_Fov;
    }

    void Camera::SetFov(const f32 fov) {
        m_Fov = fov;
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(m_Transform.GetPosition(), m_Transform.GetPosition() + m_Front, m_Up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return m_ProjectionMatrix;
    }

    Transform Camera::GetTransform() const {
        return m_Transform;
    }
}
