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
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        add_compile_options(/Zi /Zf /MDd)
    else ()
        add_compile_options(-gcodeview)
        add_link_options(-Xlinker /DEBUG)
    endif ()
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (MSVC)
        add_compile_options(/O2)
    else ()
        add_compile_options(-O2)
    endif ()
endif ()

add_subdirectory(Thirdparty)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        add_compile_options(/W4 /Wall)
    else ()
        add_compile_options(-Wall -Wextra -pedantic)
    endif ()
endif ()

add_subdirectory(Sources)
add_subdirectory(Samples)

# ---
