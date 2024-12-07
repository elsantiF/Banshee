cmake_minimum_required(VERSION 3.28)
project(Application)

# --- General Settings ---

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) # TODO: This is a hack, find a better way to do this (Assimp not found)

option(USE_HYBRID_GRAPHICS "Enable Nvidia Optimus/AMD Hybrid Graphics support" ON)
option(BANSHEE_STATIC "Build Banshee as a static library" OFF)

if (MSVC)
    add_compile_options(/MP) # Enable parallel compilation on MSVC
endif ()

# --- End General Settings ---

# --- Third Party Libraries ---

add_subdirectory(ThirdParty)

# ---

# --- Banshee Engine ---

add_subdirectory(Sources)

# ---

# --- Samples Build ---

add_subdirectory(Samples)

# ---
