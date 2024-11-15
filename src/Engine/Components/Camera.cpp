#include "Camera.h"

Camera::Camera(const float fov, const float aspect, const float near, const float far) {
    m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);

    m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    m_Yaw = 0.0f;
    m_Pitch = 0.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
    glm::vec3 front;

    const float radiansYaw = glm::radians(m_Yaw);
    const float radiansPitch = glm::radians(m_Pitch);

    front.x = cos(radiansYaw) * cos(radiansPitch);
    front.y = sin(radiansPitch);
    front.z = sin(radiansYaw) * cos(radiansPitch);

    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Camera::Update(const float delta) {
    // Position update
    const float positionSpeed = 10.0f * delta;

    if (InputManager::IsKeyPressed(GLFW_KEY_W)) {
        m_Position += m_Front * positionSpeed;
    }
    if (InputManager::IsKeyPressed(GLFW_KEY_S)) {
        m_Position -= m_Front * positionSpeed;
    }
    if (InputManager::IsKeyPressed(GLFW_KEY_D)) {
        m_Position += m_Right * positionSpeed;
    }
    if (InputManager::IsKeyPressed(GLFW_KEY_A)) {
        m_Position -= m_Right * positionSpeed;
    }
    if (InputManager::IsKeyPressed(GLFW_KEY_Q)) {
        m_Position += m_Up * positionSpeed;
    }
    if (InputManager::IsKeyPressed(GLFW_KEY_E)) {
        m_Position -= m_Up * positionSpeed;
    }

    // Rotation update
    const float rotationSpeed = 35.0f * delta;

    if(InputManager::IsKeyPressed(GLFW_KEY_DOWN)) {
        m_Pitch -= rotationSpeed;
    }
    if(InputManager::IsKeyPressed(GLFW_KEY_UP)) {
        m_Pitch += rotationSpeed;
    }
    if(InputManager::IsKeyPressed(GLFW_KEY_LEFT)) {
        m_Yaw -= rotationSpeed;
    }
    if(InputManager::IsKeyPressed(GLFW_KEY_RIGHT)) {
        m_Yaw += rotationSpeed;
    }

    if(m_Pitch > 89.0f) m_Pitch = 89.0f;
    if(m_Pitch < -89.0f) m_Pitch = -89.0f;

    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return m_ProjectionMatrix;
}

glm::vec3 Camera::GetCameraPosition() const {
    return m_Position;
}
