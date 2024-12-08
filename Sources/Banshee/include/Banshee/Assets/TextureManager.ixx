module;
#include <filesystem>

export module Banshee.Assets.TextureManager;

import Poltergeist;
import Spectre.Texture;
import Banshee.Assets.AssetManager;
import Banshee.Assets.Resource;

export namespace Banshee {
    using namespace Spectre; // TODO: This is temporary

    class TextureManager final : public ResourceManager<Texture> {
    public:
        TextureManager();

        Resource<Texture> Load(const fs::path &texturePath) override;
    };
}
