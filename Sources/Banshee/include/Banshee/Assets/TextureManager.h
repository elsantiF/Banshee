#pragma once

#include <Spectre/Texture.h>

#include "Banshee/Core/Core.h"
#include "AssetManager.h"
#include "Resource.h"

namespace Banshee {
    using namespace Spectre; // TODO: This is temporary

    class TextureManager final : public ResourceManager<Texture> {
    public:
        TextureManager();

        Resource<Texture> Load(const fs::path &texturePath) override;
    };
}
