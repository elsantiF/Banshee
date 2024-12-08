cmake_minimum_required(VERSION 3.28)
project(Application)

# --- General Settings ---

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(USE_HYBRID_GRAPHICS "Enable Nvidia Optimus/AMD Hybrid Graphics support" ON)
option(BANSHEE_STATIC "Build Banshee as a static library" OFF)

if (MSVC)
    add_compile_options(/MP) # Enable parallel compilation on MSVC
endif ()

# --- End General Settings ---

# --- Sources ---

add_subdirectory(Thirdparty)
add_subdirectory(Sources)
add_subdirectory(Samples)

# ---
