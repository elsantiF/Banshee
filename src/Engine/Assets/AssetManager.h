#pragma once

#include <filesystem>

#include "Core/Core.h"

namespace BansheeEngine {
    class AssetManager {
        inline static fs::path m_RootPath = fs::current_path();

    public:
        static void SetRoot(const fs::path &path);
        static fs::path GetRoot();
    };
}
