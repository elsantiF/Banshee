#include "Renderer.h"

namespace BansheeEngine {
    void Renderer::Init() {
        Logger::PANIC(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)),
                      "Failed to initialize GLAD");

        //glViewport(0, 0, 1280, 720);
        SetClearColor(glm::vec4{0.3f, 0.0f, 0.3f, 0.0f});
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);

        Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_VERSION)));
        Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_VENDOR)));
        Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(DebugCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }

    // TODO: Do better logging
    void APIENTRY Renderer::DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                                          const void *userParam) {
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                Logger::CRITICAL(message);
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                Logger::ERROR(message);
                break;
            case GL_DEBUG_SEVERITY_LOW:
                Logger::WARN(message);
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                Logger::INFO(message);
                break;
            default:
                Logger::INFO(message);
                break;
        }
    }

    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::SetPolygonMode(const PolygonMode mode) {
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}
