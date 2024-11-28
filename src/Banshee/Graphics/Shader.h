#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Core.h"
#include "Assets/AssetManager.h"

namespace Banshee {
    class Shader {
        String m_ShaderName;
        u32 m_ProgramID = 0;
        UnorderedMap<String, i32> m_Uniforms;

        void CheckCompilationError(u32 shaderProgram, const String &shaderType) const;
        [[nodiscard]] Pair<u32, u32> CompileShader(const String &filename) const;

    public:
        Shader() = default;
        explicit Shader(const String &filename);
        ~Shader();

        void Bind() const;
        static void Unbind();

        void SetInt(const String &uniformName, i32 value) const;
        void SetVec3(const String &uniformName, glm::vec3 vec3) const;
        void SetMat4(const String &uniformName, glm::mat4 mat4) const;
    };
}
