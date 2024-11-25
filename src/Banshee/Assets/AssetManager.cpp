#include "AssetManager.h"

namespace BansheeEngine {
    void AssetManager::SetRoot(const fs::path &path) {
        m_RootPath = fs::path(path);
    }

    fs::path AssetManager::GetRoot() {
        return m_RootPath;
    }
}
