// This file is here only to enable Tracy profiling for memory allocation on C++20 modules.
// TODO: See if this is the best place to put this code.
#include <memory>
#include <tracy/Tracy.hpp>

#ifdef TRACY_ENABLE
void *operator new(const std::size_t size) {
    const auto ptr = malloc(size);
    TracyAllocS(ptr, size, 15);
    return ptr;
}

void operator delete(void *ptr) noexcept {
    TracyFreeS(ptr, 15);
    free(ptr);
}

void *operator new[](const std::size_t size) {
    const auto ptr = malloc(size);
    TracyAllocS(ptr, size, 15);
    return ptr;
}

void operator delete[](void *ptr) noexcept {
    TracyFreeS(ptr, 15);
    free(ptr);
}
#endif
