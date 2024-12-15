module;
#include <memory>

export module Poltergeist.Memory;

export template <typename T>
using Scope = std::unique_ptr<T>;

export template <typename T, typename... Args>
Scope<T> MakeScope(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

export template <typename T>
using Ref = std::shared_ptr<T>;

export template <typename T, typename... Args>
Ref<T> MakeRef(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}
