module;
#include <filesystem>

export module Banshee.Assets.AssetManager;

import Poltergeist;
import Spectre.Shader;
import Banshee.Assets.ResourceManager;
import Banshee.Assets.ModelManager;
import Banshee.Assets.TextureManager;
import Banshee.Assets.ShaderManager;

export namespace Banshee {
    class AssetManager {
        inline static auto m_ModelManager = ModelManager();
        inline static auto m_TextureManager = TextureManager();
        inline static auto m_ShaderManager = ShaderManager();

    public:
        static auto &GetModelManager() { return m_ModelManager; }
        static auto &GetTextureManager() { return m_TextureManager; }
        static auto &GetShaderManager() { return m_ShaderManager; }
    };
}
