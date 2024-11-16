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
