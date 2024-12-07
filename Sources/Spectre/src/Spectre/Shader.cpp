#include "Spectre/Shader.h"

namespace Spectre {
#pragma region Shader class
    Shader::Shader(const String &shaderName, const ShaderType shaderType): m_ShaderName{shaderName}, m_ShaderType{shaderType} {
        m_ShaderID = glCreateShader(ShaderTypeToGLenum(shaderType));
    }

    void Shader::Compile(const String &shaderSource) const {
        // TODO: Find a better way to do this
        const char *shaderCodeChar = shaderSource.c_str();
        Logger::INFO("Compiling " + ShaderTypeToString(m_ShaderType) + " shader of: " + m_ShaderName);
        glShaderSource(m_ShaderID, 1, &shaderCodeChar, nullptr);
        glCompileShader(m_ShaderID);
        CheckCompilationError();
    }

    Shader::~Shader() {
        glDeleteShader(m_ShaderID);
    }

    void Shader::CheckCompilationError() const {
        i32 success;
        glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetShaderInfoLog(m_ShaderID, 1024, nullptr, infoLog);
            Logger::CRITICAL("Error compiling shader: " + m_ShaderName + "\nLog: " + String{infoLog});
        }
    }

    u32 Shader::GetShaderID() const {
        return m_ShaderID;
    }

    GLenum Shader::ShaderTypeToGLenum(const ShaderType shaderType) {
        switch (shaderType) {
            case VERTEX_SHADER:
                return GL_VERTEX_SHADER;
            case FRAGMENT_SHADER:
                return GL_FRAGMENT_SHADER;
            case GEOMETRY_SHADER:
                return GL_GEOMETRY_SHADER;
            case COMPUTE_SHADER:
                return GL_COMPUTE_SHADER;
            default:
                static_assert("Invalid shader type");
                return 0;
        }
    }

    String Shader::ShaderTypeToString(const ShaderType shaderType) {
        switch (shaderType) {
            case VERTEX_SHADER:
                return "Vertex";
            case FRAGMENT_SHADER:
                return "Fragment";
            case GEOMETRY_SHADER:
                return "Geometry";
            case COMPUTE_SHADER:
                return "Compute";
            default:
                static_assert("Invalid shader type");
                return "";
        }
    }

    String Shader::GetShaderExtension(const ShaderType shaderType) {
        switch (shaderType) {
            case VERTEX_SHADER:
                return ".vert";
            case FRAGMENT_SHADER:
                return ".frag";
            case GEOMETRY_SHADER:
                return ".geom";
            case COMPUTE_SHADER:
                return ".comp";
            default:
                static_assert("Invalid shader type");
                return "";
        }
    }
#pragma endregion

#pragma region ShaderProgram class
    ShaderProgram::ShaderProgram(const String &shaderName): m_ShaderProgramName{shaderName} {
        m_ProgramID = glCreateProgram();
        Logger::PANIC(m_ProgramID == 0, "Can't create shader: " + shaderName);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_ProgramID);
    }

    void ShaderProgram::AttachShader(const Shader &shader) const {
        glAttachShader(m_ProgramID, shader.GetShaderID());
    }

    void ShaderProgram::Link() {
        glLinkProgram(m_ProgramID);
        CheckCompilationError();
        GetUniforms();
    }

    void ShaderProgram::GetUniforms() {
        GLint numUniforms = 0;
        glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &numUniforms);

        // Get all uniforms
        char uniformName[256];
        GLint arraySize = 0;
        GLenum type = 0;
        GLsizei actualLength = 0;

        for (int indexUniform = 0; indexUniform < numUniforms; indexUniform++) {
            glGetActiveUniform(m_ProgramID, indexUniform, sizeof(uniformName) - 1, &actualLength, &arraySize, &type, &uniformName[0]);
            uniformName[actualLength] = 0;

            // Store uniform
            m_Uniforms[uniformName] = glGetUniformLocation(m_ProgramID, uniformName);
        }
    }

    void ShaderProgram::CheckCompilationError() const {
        i32 success;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetProgramInfoLog(m_ProgramID, 1024, nullptr, infoLog);
            Logger::CRITICAL("Error compiling shader: " + m_ShaderProgramName + "\nLog: " + String{infoLog});
        }
    }

    void ShaderProgram::Bind() const {
        glUseProgram(m_ProgramID);
    }

    void ShaderProgram::Unbind() {
        glUseProgram(0);
    }

    void ShaderProgram::SetInt(const String &uniformName, const i32 value) const {
        if (m_Uniforms.contains(uniformName)) {
            const auto uniformLocation = m_Uniforms.at(uniformName);
            glUniform1i(uniformLocation, value);
        }
    }

    void ShaderProgram::SetVec3(const String &uniformName, glm::vec3 vec3) const {
        const auto uniformLocation = m_Uniforms.at(uniformName);
        glUniform3fv(uniformLocation, 1, glm::value_ptr(vec3));
    }

    void ShaderProgram::SetMat4(const String &uniformName, glm::mat4 mat4) const {
        const auto uniformLocation = m_Uniforms.at(uniformName);
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4));
    }
#pragma endregion
}
