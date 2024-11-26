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

add_subdirectory(src/ThirdParty)

# ---

# --- Banshee Engine ---

add_subdirectory(src/Banshee)

# ---

# --- Application Build ---

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(Application src/Banshee/main.cpp)
link_directories(${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(Application PUBLIC stb glad glm assimp::assimp glad glfw imgui Banshee)

# ---

# if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#     add_compile_options(/W4 /Wall)
#     if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#         add_compile_options(/Zi /Zf)
#     else ()
#         add_compile_options(/O2)
#     endif ()
# endif ()

# --- Custom Commands ---

add_custom_command(TARGET Application POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
)

# ---
