module;
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

export module Spectre.Shader;

import Poltergeist;

export namespace Spectre {
    enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, COMPUTE_SHADER };

    class Shader {
        String m_ShaderName;
        u32 m_ShaderID = 0;
        ShaderType m_ShaderType;

        void CheckCompilationError() const;
        [[nodiscard]] static GLenum ShaderTypeToGLenum(ShaderType shaderType);
        [[nodiscard]] static String ShaderTypeToString(ShaderType shaderType);
        [[nodiscard]] static String GetShaderExtension(ShaderType shaderType);

    public:
        Shader() = delete;
        explicit Shader(const String &shaderName, ShaderType shaderType);
        ~Shader();

        void Compile(const String &shaderSource) const;
        [[nodiscard]] u32 GetShaderID() const;
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

        void SetInt(const String &uniformName, i32 value) const;
        void SetVec3(const String &uniformName, glm::vec3 vec3) const;
        void SetMat4(const String &uniformName, glm::mat4 mat4) const;
    };
}
