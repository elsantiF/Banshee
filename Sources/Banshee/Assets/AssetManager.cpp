module;
#include <fstream>
#include <sstream>
#include <Profiler/Profiler.hpp>

module Banshee.Assets.AssetManager;

namespace Banshee {
    Ref<Spectre::ShaderProgram> AssetManager::LoadShaderProgram(const fs::path &shaderName) {
        PROFILE_SCOPE();
        // TODO: Do better file reading
        std::ifstream vertexFile;
        vertexFile.open(shaderName.generic_string() + ".vert");
        Logger::PANIC(!vertexFile.is_open(), "Can't open Vertex Shader: " + shaderName.generic_string());
        std::stringstream vertexSteam;
        vertexSteam << vertexFile.rdbuf();
        vertexFile.close();
        const String vertexCode = vertexSteam.str();

        std::ifstream fragmentFile;
        fragmentFile.open(shaderName.generic_string() + ".frag");
        Logger::PANIC(!fragmentFile.is_open(), "Can't open Fragment Shader: " + shaderName.generic_string());
        std::stringstream fragmentStream;
        fragmentStream << fragmentFile.rdbuf();
        fragmentFile.close();
        const String fragmentCode = fragmentStream.str();

        auto vertexShader = Spectre::Shader{shaderName.generic_string(), Spectre::ShaderType::VERTEX_SHADER};
        vertexShader.Compile(vertexCode);
        auto fragmentShader = Spectre::Shader{shaderName.generic_string(), Spectre::ShaderType::FRAGMENT_SHADER};
        fragmentShader.Compile(fragmentCode);

        auto shaderProgram = MakeRef<Spectre::ShaderProgram>(shaderName.generic_string());
        shaderProgram->AttachShader(vertexShader);
        shaderProgram->AttachShader(fragmentShader);
        shaderProgram->Link();

        return shaderProgram;
    }
}
