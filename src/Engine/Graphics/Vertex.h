#pragma once

#include <glm/glm.hpp>

namespace BansheeEngine {
    struct Vertex {
        glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 normal = glm::vec3(0.f, 0.f, 0.f);
        glm::vec2 texCoords = glm::vec2(0.f, 0.f);
        glm::vec3 tangent = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 bitangent = glm::vec3(0.f, 0.f, 0.f);
    };
}
