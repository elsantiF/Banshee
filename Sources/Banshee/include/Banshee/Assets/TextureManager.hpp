#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Spectre/Texture/Texture.hpp>
#include "ResourceManager.hpp"

namespace Banshee {
    class TextureManager final : public ResourceManager<Spectre::Texture> {
        Ref<Spectre::Texture> Load(const fs::path &texturePath) override;

    public:
        TextureManager() = default;
    };
}
