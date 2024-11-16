#pragma once

#include <glm/glm.hpp>

namespace BansheeEngine {
    struct Transform {
        glm::vec3 translation = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
    };
}
