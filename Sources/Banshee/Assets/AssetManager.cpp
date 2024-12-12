module;
#include <fstream>
#include <sstream>
#include <tracy/Tracy.hpp>

module Banshee.Assets.AssetManager;

namespace Banshee {
    void AssetManager::SetRoot(const fs::path &path) { m_RootPath = fs::path(path); }

    fs::path AssetManager::GetRoot() { return m_RootPath; }

    Resource<Spectre::ShaderProgram> AssetManager::LoadShaderProgram(const String &shaderName) {
        ZoneScoped;
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

        auto vertexShader = Spectre::Shader{shaderName + ".vert", Spectre::ShaderType::VERTEX_SHADER};
        vertexShader.Compile(vertexCode);
        auto fragmentShader = Spectre::Shader{shaderName + ".frag", Spectre::ShaderType::FRAGMENT_SHADER};
        fragmentShader.Compile(fragmentCode);

        auto shaderProgram = MakeRef<Spectre::ShaderProgram>(shaderName);
        shaderProgram->AttachShader(vertexShader);
        shaderProgram->AttachShader(fragmentShader);
        shaderProgram->Link();

        return Resource<Spectre::ShaderProgram>{shaderProgram, shaderName};
    }
}
