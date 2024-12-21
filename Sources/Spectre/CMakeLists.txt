project(Spectre)

add_library(Spectre STATIC)

set(SPECTRE_INCLUDE_FILES
        include/Spectre/Buffer/Buffer.hpp
        include/Spectre/Framebuffer/Framebuffer.hpp
        include/Spectre/Renderbuffer/Renderbuffer.hpp
        include/Spectre/Renderer/Renderer.hpp
        include/Spectre/Shader/Shader.hpp
        include/Spectre/Texture/Texture.hpp
        include/Spectre/Vertex/Vertex.hpp
        include/Spectre/VertexArray/VertexArray.hpp
)

set(SPECTRE_SOURCE_FILES
        src/Buffer/Buffer.cpp
        src/Framebuffer/Framebuffer.cpp
        src/Renderbuffer/Renderbuffer.cpp
        src/Renderer/Renderer.cpp
        src/Shader/Shader.cpp
        src/Texture/Texture.cpp
        src/VertexArray/VertexArray.cpp
)

target_include_directories(Spectre
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(Spectre
        PRIVATE
        ${SPECTRE_SOURCE_FILES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        ${SPECTRE_INCLUDE_FILES}
)

target_link_libraries(Spectre
        PUBLIC
        glm::glm
        glfw
        glad
        Poltergeist
)

install(TARGETS Spectre glm glfw
        EXPORT SpectreTargets
        FILE_SET HEADERS
)

install(EXPORT SpectreTargets
        FILE SpectreTargets.cmake
        NAMESPACE Spectre::
        DESTINATION lib/cmake/Spectre
)
