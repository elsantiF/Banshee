project(Banshee)

if (BANSHEE_STATIC)
    add_library(Banshee STATIC)
else ()
    add_library(Banshee SHARED)
endif ()

if (USE_HYBRID_GRAPHICS AND WIN32)
    target_compile_definitions(Banshee PUBLIC
            BE_OVER_9000 # Enables Nvidia Optimus/AMD Hybrid Graphics support
    )
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Banshee PRIVATE
            BE_DEBUG
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Banshee PRIVATE
            BE_RELEASE
    )
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(Banshee PRIVATE /W4 /Wall /Zi /Zf /MDd)
    else ()
        target_compile_options(Banshee PRIVATE -Wall -Wextra -pedantic)
    endif ()
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (MSVC)
        target_compile_options(Banshee PRIVATE /O2)
    else ()
        target_compile_options(Banshee PRIVATE -O2)
    endif ()
endif ()

target_sources(Banshee PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        # Assets
        include/Banshee/Assets/AssetManager.ixx
        include/Banshee/Assets/ModelManager.ixx
        include/Banshee/Assets/Resource.ixx
        include/Banshee/Assets/TextureManager.ixx

        # Components
        include/Banshee/Components/Camera.ixx
        include/Banshee/Components/Model.ixx
        include/Banshee/Components/StaticMesh.ixx
        include/Banshee/Components/Transform.ixx

        # Core
        include/Banshee/Core/Application.ixx
        include/Banshee/Core/InputManager.ixx
        include/Banshee/Core/Level.ixx
        include/Banshee/Core/Window.ixx
)

target_sources(Banshee PUBLIC
        # Assets
        src/Banshee/Assets/AssetManager.cpp
        src/Banshee/Assets/ModelManager.cpp
        src/Banshee/Assets/TextureManager.cpp

        # Components
        src/Banshee/Components/Camera.cpp
        src/Banshee/Components/Model.cpp
        src/Banshee/Components/StaticMesh.cpp
        src/Banshee/Components/Transform.cpp

        # Core
        src/Banshee/Core/Application.cpp
        src/Banshee/Core/InputManager.cpp
        src/Banshee/Core/Window.cpp
)

target_link_libraries(Banshee stb glm::glm assimp::assimp glad glfw imgui Poltergeist Spectre)
