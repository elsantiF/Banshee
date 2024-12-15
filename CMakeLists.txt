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

add_subdirectory(Thirdparty)
add_subdirectory(Sources)
add_subdirectory(Samples)

# ---
