#include "Shader.h"

void Shader::Init(const std::string &filename) {
    m_ShaderName = filename;
    m_ProgramID = glCreateProgram();
    Logger::PANIC(m_ProgramID == 0, "Can't create shader: " + filename);

    const auto [vertexShader, fragmentShader] = CompileShader(filename);

    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    int success;

    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(m_ProgramID, 1024, nullptr, infoLog);
        Logger::CRITICAL("Error compiling shader: " + m_ShaderName + "\nLog: " + std::string{infoLog});
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

void Shader::Clear() const {
    glDeleteProgram(m_ProgramID);
}

void Shader::CheckCompilationError(const unsigned int shaderProgram, const std::string &shaderType) const {
    int success;
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderProgram, 1024, nullptr, infoLog);
        Logger::CRITICAL("Error linking the shader: " + m_ShaderName + "\nLog: " + std::string{infoLog});
    }
}

std::pair<unsigned int, unsigned int> Shader::CompileShader(const std::string &shaderName) const {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    vertexShaderFile.open(shaderName + ".vert");
    fragmentShaderFile.open(shaderName + ".frag");

    Logger::PANIC(!vertexShaderFile.is_open(), "Can't open vertex shader: " + shaderName);
    Logger::PANIC(!fragmentShaderFile.is_open(), "Can't open fragment shader: " + shaderName);

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();


    const char *vertxShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();

    Logger::INFO("Compiling vertex shader of: " + shaderName);
    glShaderSource(vertexShader, 1, &vertxShaderCode, nullptr);
    glCompileShader(vertexShader);
    CheckCompilationError(vertexShader, "Vertex");

    Logger::INFO("Compiling fragment shader of: " + shaderName);
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

void Shader::SetMat4Uniform(const std::string &uniformName, glm::mat4 mat4) const {
    const auto uniformLocation = m_Uniforms.at(uniformName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::SetVec3Uniform(const std::string &uniformName, glm::vec3 vec3) const {
    const auto uniformLocation = m_Uniforms.at(uniformName);
    glUniform3fv(uniformLocation, 1, glm::value_ptr(vec3));
}
