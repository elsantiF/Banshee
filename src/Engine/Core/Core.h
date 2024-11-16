#pragma once

#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include "Logger.h"

namespace BansheeEngine {
#pragma region Memory Macros
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    UniquePtr<T> MakeUnique(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
#pragma endregion

#pragma region Container Macros
    template<typename T>
    using Vector = std::vector<T>;
#pragma endregion
}
