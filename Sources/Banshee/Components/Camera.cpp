module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

module Banshee.Components.Camera;

namespace Banshee {
    Camera::Camera(const f32 fov, const f32 aspect, const f32 near, const f32 far) : m_Fov{fov}, m_Aspect{aspect}, m_Near{near}, m_Far{far} {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
    }
}
