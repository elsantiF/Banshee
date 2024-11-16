#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Core/Core.h"

namespace BansheeEngine {
    enum PolygonMode {
        FILL = GL_FILL,
        LINE = GL_LINE,
        POINT = GL_POINT
    };

    class Renderer {
    public:
        static void Init();

        static void Clear();
        static void SetClearColor(const glm::vec4 &color);
        static void SetPolygonMode(PolygonMode mode);
    };
}
