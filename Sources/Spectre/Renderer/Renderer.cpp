module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <Profiler/Profiler.hpp>

module Spectre.Renderer;

namespace Spectre {
    void Renderer::Init() {
        PROFILE_SCOPE();
        Logger::PANIC(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)), "Failed to initialize GLAD");

        // glViewport(0, 0, 1280, 720);
        SetClearColor(glm::vec4{0.3f, 0.0f, 0.3f, 0.0f});
        glEnable(GL_MULTISAMPLE);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_VERSION)));
        Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_VENDOR)));
        Logger::INFO(reinterpret_cast<const char *const>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

        i32 flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(DebugCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        PROFILE_GPU_CONTEXT();
    }

    // TODO: Do better logging
    void APIENTRY Renderer::DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                                          const void *userParam) {
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        String sourceString;
        switch (source) {
        case GL_DEBUG_SOURCE_API:           sourceString = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceString = "Window System"; break;
        case GL_SHADER_COMPILER:            sourceString = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:   sourceString = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:   sourceString = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:
        default:                            sourceString = "Other";
        }

        String typeString;
        switch (type) {
        case GL_DEBUG_TYPE_ERROR:               typeString = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "Deprecated Behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeString = "Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         typeString = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         typeString = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              typeString = "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          typeString = "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           typeString = "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:
        default:                                typeString = "Other";
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            Logger::ERROR("OpenGL Debug Message - ID: " + std::to_string(id) + "\n\t| Source: " + sourceString + "\n\t| Type: " + typeString +
                          "\n\t| Severity: High\nMessage: " + message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            Logger::WARN("OpenGL Debug Message - ID: " + std::to_string(id) + "\n\t| Source: " + sourceString + "\n\t| Type: " + typeString +
                         "\n\t| Severity: Medium\nMessage: " + message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            Logger::INFO("OpenGL Debug Message - ID: " + std::to_string(id) + "\n\t| Source: " + sourceString + "\n\t| Type: " + typeString +
                         "\n\t| Severity: Low\nMessage: " + message);
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            Logger::INFO("OpenGL Debug Message - ID: " + std::to_string(id) + "\n\t| Source: " + sourceString + "\n\t| Type: " + typeString +
                         "\n\t| Severity: Notification\nMessage: " + message);
            break;
        default:
            Logger::INFO("OpenGL Debug Message - ID: " + std::to_string(id) + "\n\t| Source: " + sourceString + "\n\t| Type: " + typeString +
                         "\n\t| Severity: Unknown\nMessage: " + message);
        }
    }

    void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::SetClearColor(const glm::vec4 &color) { glClearColor(color.r, color.g, color.b, color.a); }

    void Renderer::SetPolygonMode(const PolygonMode mode) {
        // This method is profiled because I think takes a long time to execute
        PROFILE_GPU_ZONE();
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}
