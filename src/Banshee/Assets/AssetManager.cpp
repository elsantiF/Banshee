#include "AssetManager.h"

namespace Banshee {
    void AssetManager::SetRoot(const fs::path &path) {
        m_RootPath = fs::path(path);
    }

    fs::path AssetManager::GetRoot() {
        return m_RootPath;
    }
}
