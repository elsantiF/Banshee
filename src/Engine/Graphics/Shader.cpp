#include "Shader.h"

namespace BansheeEngine {
    Shader::Shader(const String &filename) {
        m_ShaderName = filename;
        m_ProgramID = glCreateProgram();
        Logger::PANIC(m_ProgramID == 0, "Can't create shader: " + filename);

        const auto [vertexShader, fragmentShader] = CompileShader(AssetManager::GetRoot().generic_string() + "/" + filename);

        glAttachShader(m_ProgramID, vertexShader);
        glAttachShader(m_ProgramID, fragmentShader);
        glLinkProgram(m_ProgramID);

        int success;

        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetProgramInfoLog(m_ProgramID, 1024, nullptr, infoLog);
            Logger::CRITICAL("Error compiling shader: " + m_ShaderName + "\nLog: " + String{infoLog});
        }

        GLint numUniforms = 0;
        glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &numUniforms);

        // Get all uniforms
        char uniformName[256];
        GLint arraySize = 0;
        GLenum type = 0;
        GLsizei actualLength = 0;

        for (int indexUniform = 0; indexUniform < numUniforms; indexUniform++) {
            glGetActiveUniform(m_ProgramID, indexUniform, sizeof(uniformName) - 1,
                               &actualLength, &arraySize, &type, &uniformName[0]);
            uniformName[actualLength] = 0;

            // Store uniform
            m_Uniforms[uniformName] = glGetUniformLocation(m_ProgramID, uniformName);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(m_ProgramID);
    }

    void Shader::CheckCompilationError(const unsigned int shaderProgram, const String &shaderType) const {
        int success;
        glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetShaderInfoLog(shaderProgram, 1024, nullptr, infoLog);
            Logger::CRITICAL("Error linking the shader: " + m_ShaderName + "\nLog: " + String{infoLog});
        }
    }

    Pair<unsigned int, unsigned int> Shader::CompileShader(const String &filename) const {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        String vertexCode;
        String fragmentCode;
        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;

        vertexShaderFile.open(filename + ".vert");
        fragmentShaderFile.open(filename + ".frag");

        Logger::PANIC(!vertexShaderFile.is_open(), "Can't open vertex shader: " + filename);
        Logger::PANIC(!fragmentShaderFile.is_open(), "Can't open fragment shader: " + filename);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();


        const char *vertxShaderCode = vertexCode.c_str();
        const char *fragmentShaderCode = fragmentCode.c_str();

        Logger::INFO("Compiling vertex shader of: " + filename);
        glShaderSource(vertexShader, 1, &vertxShaderCode, nullptr);
        glCompileShader(vertexShader);
        CheckCompilationError(vertexShader, "Vertex");

        Logger::INFO("Compiling fragment shader of: " + filename);
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
        glCompileShader(fragmentShader);
        CheckCompilationError(fragmentShader, "Fragment");

        return std::make_pair(vertexShader, fragmentShader);
    }

    void Shader::Bind() const {
        glUseProgram(m_ProgramID);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    void Shader::SetInt(const String &uniformName, int value) const {
        if (m_Uniforms.contains(uniformName)) {
            const auto uniformLocation = m_Uniforms.at(uniformName);
            glUniform1i(uniformLocation, value);
        }
    }

    void Shader::SetVec3(const String &uniformName, glm::vec3 vec3) const {
        const auto uniformLocation = m_Uniforms.at(uniformName);
        glUniform3fv(uniformLocation, 1, glm::value_ptr(vec3));
    }

    void Shader::SetMat4(const String &uniformName, glm::mat4 mat4) const {
        const auto uniformLocation = m_Uniforms.at(uniformName);
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4));
    }
}
