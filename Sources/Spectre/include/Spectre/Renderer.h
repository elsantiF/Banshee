#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Poltergeist/Poltergeist.h>

namespace Spectre {
    enum PolygonMode {
        FILL = GL_FILL,
        LINE = GL_LINE,
        POINT = GL_POINT
    };

    class Renderer {
        static void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                                           const void *userParam);

    public:
        static void Init();

        static void Clear();
        static void SetClearColor(const glm::vec4 &color);
        static void SetPolygonMode(PolygonMode mode);
    };
}
