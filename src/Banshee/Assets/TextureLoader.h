#pragma once

#include "Core/Core.h"
#include "Graphics/Texture.h"
#include "AssetManager.h"
#include "Resource.h"

namespace Banshee {
    class TextureLoader final : public ResourceImporter<Texture> {
    public:
        TextureLoader();

        Resource<Texture> Load(const fs::path &texturePath) override;
    };
}
