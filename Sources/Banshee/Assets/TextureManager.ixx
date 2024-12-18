module;
#include <filesystem>

export module Banshee.Assets.TextureManager;

import Poltergeist;
import Spectre.Texture;
import Banshee.Assets.ResourceManager;

export namespace Banshee {
    class TextureManager final : public ResourceManager<Spectre::Texture> {
        Ref<Spectre::Texture> Load(const fs::path &texturePath) override;

    public:
        TextureManager();
    };
}
