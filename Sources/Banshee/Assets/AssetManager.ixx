module;
#include <filesystem>

export module Banshee.Assets.AssetManager;

import Poltergeist;
import Spectre.Shader;
import Banshee.Assets.ResourceManager;
import Banshee.Assets.ModelManager;
import Banshee.Assets.TextureManager;

export namespace Banshee {
    class AssetManager {
        inline static auto m_ModelManager = ModelManager();
        inline static auto m_TextureManager = TextureManager();

    public:
        // TODO: This is temporary, it will be moved to another place
        static Ref<Spectre::ShaderProgram> LoadShaderProgram(const fs::path &shaderName);

        static ModelManager &GetModelManager() { return m_ModelManager; }
        static TextureManager &GetTextureManager() { return m_TextureManager; }
    };
}
