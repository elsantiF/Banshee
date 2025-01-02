#include "Banshee/Assets/TextureManager.hpp"

#ifdef TRACY_ENABLE
void *TraceMalloc(size_t size) {
    void *ptr = malloc(size);
    PROFILE_MEM_ALLOC(ptr, size);
    return ptr;
}

void *TraceRealloc(void *ptr, size_t newSize) {
    PROFILE_MEM_FREE(ptr);
    ptr = realloc(ptr, newSize);
    PROFILE_MEM_ALLOC(ptr, newSize);
    return ptr;
}

void TraceFree(void *ptr) {
    PROFILE_MEM_FREE(ptr);
    free(ptr);
}

#define STBI_MALLOC(size) TraceMalloc(size)
#define STBI_REALLOC(ptr, newSize) TraceRealloc(ptr, newSize)
#define STBI_FREE(ptr) TraceFree(ptr)

#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Banshee {
    Ref<Spectre::Texture> TextureManager::Load(const fs::path &texturePath) {
        PROFILE_SCOPE();
        Logger::INFO("Loading texture: " + texturePath.generic_string());
        int width, height, channels;
        u8 *data = stbi_load(texturePath.generic_string().c_str(), &width, &height, &channels, 0);
        if (!data) {
            Logger::CRITICAL("Error loading texture: " + texturePath.generic_string());
        }

        Spectre::TextureSpec spec{.width = static_cast<u32>(width), .height = static_cast<u32>(height), .channels = static_cast<u32>(channels)};

        const auto m_Resource = MakeRef<Spectre::Texture>(spec, data);

        stbi_image_free(data);

        return m_Resource;
    }
}
