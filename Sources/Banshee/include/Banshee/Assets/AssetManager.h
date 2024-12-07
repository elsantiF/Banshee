#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <Spectre/Shader.h>

#include "Banshee/Core/Core.h"
#include "Resource.h"

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
