#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "Resource.h"
#include "Core/Core.h"
#include "Graphics/Shader.h"

namespace Banshee {
    class ShaderProgram;

    class AssetManager {
        inline static fs::path m_RootPath = fs::current_path();

    public:
        static void SetRoot(const fs::path &path);
        static fs::path GetRoot();

        static Resource<ShaderProgram> LoadShaderProgram(const String &shaderName);
    };
}
