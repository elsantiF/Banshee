module;
#include <filesystem>
#include <tracy/Tracy.hpp>

#ifdef TRACY_ENABLE
void *TraceMalloc(size_t size) {
    void *ptr = malloc(size);
    TracyAllocS(ptr, size, 15);
    return ptr;
}

void *TraceRealloc(void *ptr, size_t newSize) {
    TracyFreeS(ptr, 15);
    ptr = realloc(ptr, newSize);
    TracyAllocS(ptr, newSize, 15);
    return ptr;
}

void TraceFree(void *ptr) {
    TracyFreeS(ptr, 15);
    free(ptr);
}

#define STBI_MALLOC(size) TraceMalloc(size)
#define STBI_REALLOC(ptr, newSize) TraceRealloc(ptr, newSize)
#define STBI_FREE(ptr) TraceFree(ptr)

#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

module Banshee.Assets.TextureManager;

namespace Banshee {
    TextureManager::TextureManager() { stbi_set_flip_vertically_on_load(true); }

    Resource<Spectre::Texture> TextureManager::Load(const fs::path &texturePath) {
        ZoneScoped;
        Logger::INFO("Loading texture: " + texturePath.generic_string());
        int width, height, channels;
        u8 *data = stbi_load(texturePath.generic_string().c_str(), &width, &height, &channels, 0);
        if (!data) {
            Logger::CRITICAL("Error loading texture: " + texturePath.generic_string());
        }

        Spectre::TextureSpec spec{.width = static_cast<u32>(width), .height = static_cast<u32>(height), .channels = static_cast<u32>(channels)};

        const auto m_Resource = MakeRef<Spectre::Texture>(spec, data);

        stbi_image_free(data);

        return Resource<Spectre::Texture>{m_Resource, texturePath};
    }
}
