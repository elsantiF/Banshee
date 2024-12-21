#include <memory>
#include "Poltergeist/Profiler/Profiler.hpp"

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
