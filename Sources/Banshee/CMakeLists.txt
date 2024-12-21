project(Banshee)

add_library(Banshee STATIC)

if (USE_HYBRID_GRAPHICS AND WIN32)
    target_compile_definitions(Banshee PUBLIC
            BE_OVER_9000 # Enables Nvidia Optimus/AMD Hybrid Graphics support
    )
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Banshee PRIVATE
            BE_DEBUG
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Banshee PRIVATE
            BE_RELEASE
    )
endif()

set(BANSHEE_SOURCES
        # Assets
        src/Assets/ModelManager.cpp
        src/Assets/ShaderManager.cpp
        src/Assets/TextureManager.cpp

        # Components
        src/Components/Camera.cpp
        src/Components/Model.cpp
        src/Components/StaticMesh.cpp
        src/Components/Transform.cpp

        # Core
        src/Core/Application.cpp
        src/Core/InputManager.cpp
        src/Core/Window.cpp

        # World
        src/World/World.cpp
)

set(BANSHEE_HEADERS
        # Assets
        include/Banshee/Assets/AssetManager.hpp
        include/Banshee/Assets/ModelManager.hpp
        include/Banshee/Assets/ResourceManager.hpp
        include/Banshee/Assets/ShaderManager.hpp
        include/Banshee/Assets/TextureManager.hpp

        # Components
        include/Banshee/Components/Camera.hpp
        include/Banshee/Components/Component.hpp
        include/Banshee/Components/Model.hpp
        include/Banshee/Components/StaticMesh.hpp
        include/Banshee/Components/Transform.hpp

        # Core
        include/Banshee/Core/Application.hpp
        include/Banshee/Core/InputManager.hpp
        include/Banshee/Core/Window.hpp

        # World
        include/Banshee/World/Entity.hpp
        include/Banshee/World/Level.hpp
        include/Banshee/World/World.hpp
)

target_sources(Banshee
        PRIVATE
        ${BANSHEE_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        ${BANSHEE_HEADERS}
)

target_include_directories(Banshee
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Banshee
        PUBLIC
        stb
        glm::glm
        assimp::assimp
        glad
        glfw
        imgui
        Poltergeist
        Spectre
)

install(TARGETS Banshee stb glm assimp zlibstatic glfw imgui
        EXPORT BansheeTargets
        FILE_SET HEADERS DESTINATION include/Banshee
)

install(EXPORT BansheeTargets
        FILE BansheeConfig.cmake
        NAMESPACE Banshee::
        DESTINATION lib/cmake/Banshee
)