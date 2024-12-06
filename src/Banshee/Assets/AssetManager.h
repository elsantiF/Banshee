#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <Shader.h> // TODO: Change this to <Spectre/Shader.h>

#include "Resource.h"
#include "Core/Core.h"

namespace Banshee {
    using namespace Spectre; // TODO: This is temporary

    class AssetManager {
        inline static fs::path m_RootPath = fs::current_path();

    public:
        static void SetRoot(const fs::path &path);
        static fs::path GetRoot();

        static Resource<ShaderProgram> LoadShaderProgram(const String &shaderName);
    };
}
