#include "AssetManager.h"

namespace BansheeEngine {
    void AssetManager::SetRoot(const String &path) {
        m_RootPath = path + "/";
    }

    String AssetManager::GetRoot() {
        return m_RootPath;
    }
}
