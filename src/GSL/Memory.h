#pragma once

#include <memory>

namespace GSL {
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    UniquePtr<T> MakeUnique(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    Ref<T> MakeRef(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
