#include "Banshee/Assets/AssetManager.h"

namespace Banshee {
    void AssetManager::SetRoot(const fs::path &path) {
        m_RootPath = fs::path(path);
    }

    fs::path AssetManager::GetRoot() {
        return m_RootPath;
    }

    Resource<ShaderProgram> AssetManager::LoadShaderProgram(const String &shaderName) {
        // TODO: Do better file reading
        std::ifstream vertexFile;
        vertexFile.open(GetRoot().generic_string() + "/" + shaderName + ".vert");
        Logger::PANIC(!vertexFile.is_open(), "Can't open Vertex Shader: " + shaderName);
        std::stringstream vertexSteam;
        vertexSteam << vertexFile.rdbuf();
        vertexFile.close();
        const String vertexCode = vertexSteam.str();

        std::ifstream fragmentFile;
        fragmentFile.open(GetRoot().generic_string() + "/" + shaderName + ".frag");
        Logger::PANIC(!fragmentFile.is_open(), "Can't open Fragment Shader: " + shaderName);
        std::stringstream fragmentStream;
        fragmentStream << fragmentFile.rdbuf();
        fragmentFile.close();
        const String fragmentCode = fragmentStream.str();

        auto vertexShader = Shader{shaderName + ".vert", ShaderType::VERTEX_SHADER};
        vertexShader.Compile(vertexCode);
        auto fragmentShader = Shader{shaderName + ".frag", ShaderType::FRAGMENT_SHADER};
        fragmentShader.Compile(fragmentCode);

        auto shaderProgram = MakeRef<ShaderProgram>(shaderName);
        shaderProgram->AttachShader(vertexShader);
        shaderProgram->AttachShader(fragmentShader);
        shaderProgram->Link();

        return Resource<ShaderProgram>{shaderProgram, shaderName};
    }
}
