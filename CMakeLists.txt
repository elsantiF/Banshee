cmake_minimum_required(VERSION 3.28)
project(Application) # TODO: Remember to change this to another name

# --- General Settings ---

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(USE_HYBRID_GRAPHICS "Enable Nvidia Optimus/AMD Hybrid Graphics support" ON)
option(ENABLE_PROFILER "Enable Tracy Profiler" OFF)

if (MSVC)
    add_compile_options(/MP) # Enable parallel compilation on MSVC
endif ()

# --- End General Settings ---

# --- Sources ---

if (ENABLE_PROFILER)
    set(TRACY_ENABLE ON CACHE BOOL "" FORCE)
    set(TRACY_CALLSTACK ON CACHE BOOL "" FORCE)
else ()
    set(TRACY_ENABLE OFF CACHE BOOL "" FORCE) # Why this else is needed? I don't know
endif ()

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0 -fomit-frame-pointer -ffunction-sections -fdata-sections")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -gcodeview")

    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections -Wl,--icf=all -s")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} -Xlinker /DEBUG")

    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
else ()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Zf /MDd")
endif ()

add_subdirectory(Thirdparty)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4 /Wall")
endif ()

add_subdirectory(Sources)
add_subdirectory(Samples)

# ---
