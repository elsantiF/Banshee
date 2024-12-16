project(Banshee)

add_library(Banshee STATIC)

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

target_sources(Banshee PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        # Assets
        Assets/AssetManager.ixx
        Assets/ModelManager.ixx
        Assets/ResourceManager.ixx
        Assets/ShaderManager.ixx
        Assets/TextureManager.ixx

        # Components
        Components/Camera.ixx
        Components/Component.ixx
        Components/Model.ixx
        Components/StaticMesh.ixx
        Components/Transform.ixx

        # Core
        Core/Application.ixx
        Core/InputManager.ixx
        Core/Window.ixx

        # World
        World/Level.ixx
        World/World.ixx
)

target_sources(Banshee PUBLIC
        # Assets
        Assets/ModelManager.cpp
        Assets/ShaderManager.cpp
        Assets/TextureManager.cpp

        # Components
        Components/Camera.cpp
        Components/Model.cpp
        Components/StaticMesh.cpp
        Components/Transform.cpp

        # Core
        Core/Application.cpp
        Core/InputManager.cpp
        Core/Window.cpp

        # World
        World/World.cpp
)

target_link_libraries(Banshee stb glm::glm assimp::assimp glad glfw imgui Poltergeist Spectre)
