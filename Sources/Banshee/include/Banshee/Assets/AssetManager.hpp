#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include "ResourceManager.hpp"
#include "ModelManager.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"

namespace Banshee {
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
