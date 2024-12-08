module;
#define STB_IMAGE_IMPLEMENTATION
#include <filesystem>
#include <stb_image.h>

module Banshee.Assets.TextureManager;

namespace Banshee {
    TextureManager::TextureManager() { stbi_set_flip_vertically_on_load(true); }

    Resource<Texture> TextureManager::Load(const fs::path &texturePath) {
        int width, height, channels;
        u8 *data = stbi_load(texturePath.generic_string().c_str(), &width, &height, &channels, 0);
        if (!data) {
            Logger::CRITICAL("Error loading texture: " + texturePath.generic_string());
        }

        TextureSpec spec{.width = static_cast<u32>(width), .height = static_cast<u32>(height), .channels = static_cast<u32>(channels)};

        const auto m_Resource = MakeRef<Texture>(spec, data);

        stbi_image_free(data);

        return Resource<Texture>{m_Resource, texturePath};
    }
}
