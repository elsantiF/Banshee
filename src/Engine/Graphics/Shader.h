#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Logger.h"

namespace BansheeEngine {
    class Shader {
        std::string m_ShaderName;
        unsigned int m_ProgramID = 0;
        std::map<std::string, int> m_Uniforms;

        void CheckCompilationError(unsigned int shaderProgram, const std::string &shaderType) const;

        [[nodiscard]] std::pair<unsigned int, unsigned int> CompileShader(const std::string &filename) const;

    public:
        void Init(const std::string &filename);
        void Clear() const;
        void Bind() const;
        static void Unbind();

        void SetMat4Uniform(const std::string &uniformName, glm::mat4 mat4) const;
        void SetVec3Uniform(const std::string &uniformName, glm::vec3 vec3) const;
    };
}
