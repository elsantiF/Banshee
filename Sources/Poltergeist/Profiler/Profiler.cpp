// This file is here only to enable Tracy profiling for memory allocation on C++20 modules.
#include <memory>
#include "Profiler.hpp"

#ifdef TRACY_ENABLE
void *operator new(const std::size_t size) {
    const auto ptr = malloc(size);
    PROFILE_MEM_ALLOC(ptr, size);
    return ptr;
}

void operator delete(void *ptr) noexcept {
    PROFILE_MEM_FREE(ptr);
    free(ptr);
}

void *operator new[](const std::size_t size) {
    const auto ptr = malloc(size);
    PROFILE_MEM_ALLOC(ptr, size);
    return ptr;
}

void operator delete[](void *ptr) noexcept {
    PROFILE_MEM_FREE(ptr);
    free(ptr);
}
#endif
