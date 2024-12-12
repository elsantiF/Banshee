module;
#include <memory>
#include <tracy/Tracy.hpp>

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

#ifdef TRACY_ENABLE
export void *operator new(const std::size_t size) {
    const auto ptr = malloc(size);
    TracyAllocS(ptr, size, 15);
    return ptr;
}

export void operator delete(void *ptr) noexcept {
    TracyFreeS(ptr, 15);
    free(ptr);
}

export void *operator new[](const std::size_t size) {
    const auto ptr = malloc(size);
    TracyAllocS(ptr, size, 15);
    return ptr;
}

export void operator delete[](void *ptr) noexcept {
    TracyFreeS(ptr, 15);
    free(ptr);
}
#endif
