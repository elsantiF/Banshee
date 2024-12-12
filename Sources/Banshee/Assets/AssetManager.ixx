module;
#include <filesystem>

export module Banshee.Assets.AssetManager;

import Poltergeist;
import Spectre.Shader;
import Banshee.Assets.Resource;

export namespace Banshee {
    class AssetManager {
        inline static fs::path m_RootPath = fs::current_path();

    public:
        static void SetRoot(const fs::path &path);
        static fs::path GetRoot();

        static Resource<Spectre::ShaderProgram> LoadShaderProgram(const String &shaderName);
    };
}
