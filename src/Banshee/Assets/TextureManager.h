#pragma once

#include "Core/Core.h"
#include "Graphics/Texture.h"
#include "AssetManager.h"
#include "Resource.h"

namespace Banshee {
    class TextureManager final : public ResourceManager<Texture> {
    public:
        TextureManager();

        Resource<Texture> Load(const fs::path &texturePath) override;
    };
}
