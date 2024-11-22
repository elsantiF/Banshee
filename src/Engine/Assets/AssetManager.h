#pragma once

#include "Core/Core.h"

namespace BansheeEngine {
    class AssetManager {
      inline static String m_RootPath = "";
    public:
        static void SetRoot(const String &path);
        static String GetRoot();
    };
}
