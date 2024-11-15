#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/InputManager.h"
#include "Core/Window.h"

// TODO: Refactor this class to use Transform class
// TODO: Refactor this to remove m_Window
class Camera {
    glm::mat4 m_ProjectionMatrix{};

    glm::vec3 m_Position{};
    glm::vec3 m_Front{};
    glm::vec3 m_Up{};
    glm::vec3 m_Right{};
    glm::vec3 m_WorldUp{};

    float m_Yaw = 0.f;
    float m_Pitch = 0.f;

    void UpdateCameraVectors();

public:
    Camera() = default;
    Camera(float fov, float aspect, float near, float far);
    void Update(float delta);
    [[nodiscard]] glm::mat4 GetViewMatrix() const;
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const;
    [[nodiscard]] glm::vec3 GetCameraPosition() const;
};
