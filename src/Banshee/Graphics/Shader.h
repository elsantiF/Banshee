#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Core.h"
#include "Assets/AssetManager.h"

namespace BansheeEngine {
    class Shader {
        String m_ShaderName;
        unsigned int m_ProgramID = 0;
        UnorderedMap<String, int> m_Uniforms;

        void CheckCompilationError(unsigned int shaderProgram, const String &shaderType) const;
        [[nodiscard]] Pair<unsigned int, unsigned int> CompileShader(const String &filename) const;

    public:
        Shader() = default;
        explicit Shader(const String &filename);
        ~Shader();

        void Bind() const;
        static void Unbind();

        void SetInt(const String &uniformName, int value) const;
        void SetVec3(const String &uniformName, glm::vec3 vec3) const;
        void SetMat4(const String &uniformName, glm::mat4 mat4) const;
    };
}