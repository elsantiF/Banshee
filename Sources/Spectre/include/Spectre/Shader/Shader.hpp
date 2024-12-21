#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Poltergeist/Poltergeist.hpp>

namespace Spectre {
    enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, COMPUTE_SHADER };

    class Shader {
        String m_ShaderName;
        u32 m_ShaderID = 0;
        ShaderType m_ShaderType;

        void CheckCompilationError() const;

    public:
        Shader() = delete;
        explicit Shader(const String &shaderName, ShaderType shaderType);
        ~Shader();

        void Compile(const String &shaderSource) const;
        [[nodiscard]] u32 GetShaderID() const { return m_ShaderID; }
    };

    class ShaderProgram {
        String m_ShaderProgramName;
        u32 m_ProgramID = 0;
        UnorderedMap<String, i32> m_Uniforms;

        void GetUniforms();
        void CheckCompilationError() const;

    public:
        ShaderProgram() = delete;
        explicit ShaderProgram(const String &shaderName);
        ~ShaderProgram();

        void Bind() const;
        void Unbind();

        void AttachShader(const Shader &shader) const;
        void Link();

        void Set(const String &uniformName, i32 value) const;
        void Set(const String &uniformName, glm::vec3 vec3) const;
        void Set(const String &uniformName, glm::mat4 mat4) const;
    };
}
