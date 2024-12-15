#pragma once
// This file only exist to easier implementation of Tracy, will be removed in the far future.
#ifdef TRACY_ENABLE

#include <glad/glad.h>
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>

#ifdef _MSC_VER
#define FUNCTION_SIGNATURE __FUNCTION__
#else
#define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif

#define PROFILE_DEPTH 15
#define PROFILE_SCOPE() ZoneScopedNS(FUNCTION_SIGNATURE, PROFILE_DEPTH)

#define PROFILE_MEM_ALLOC(ptr, size) TracyAllocS(ptr, size, PROFILE_DEPTH)
#define PROFILE_MEM_FREE(ptr) TracyFreeS(ptr, PROFILE_DEPTH)

#define PROFILE_GPU_CONTEXT() TracyGpuContext
#define PROFILE_GPU_COLLECT() TracyGpuCollect
#define PROFILE_GPU_ZONE() PROFILE_SCOPE(); TracyGpuZoneS(FUNCTION_SIGNATURE, PROFILE_DEPTH)

#define PROFILE_FRAME_MARK() FrameMark

#endif
