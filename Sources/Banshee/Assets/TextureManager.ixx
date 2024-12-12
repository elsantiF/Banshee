module;
#include <filesystem>

export module Banshee.Assets.TextureManager;

import Poltergeist;
import Spectre.Texture;
import Banshee.Assets.AssetManager;
import Banshee.Assets.Resource;

export namespace Banshee {
    class TextureManager final : public ResourceManager<Spectre::Texture> {
    public:
        TextureManager();

        Resource<Spectre::Texture> Load(const fs::path &texturePath) override;
    };
}
