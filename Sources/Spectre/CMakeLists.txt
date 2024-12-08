project(Spectre)

add_library(Spectre STATIC)

target_sources(Spectre PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        include/Spectre/Framebuffer.ixx
        include/Spectre/GraphicBuffer.ixx
        include/Spectre/Renderbuffer.ixx
        include/Spectre/Renderer.ixx
        include/Spectre/Shader.ixx
        include/Spectre/Spectre.ixx
        include/Spectre/Texture.ixx
        include/Spectre/Vertex.ixx
        include/Spectre/VertexArray.ixx
)

target_sources(Spectre PUBLIC
        src/Spectre/Framebuffer.cpp
        src/Spectre/GraphicBuffer.cpp
        src/Spectre/Renderbuffer.cpp
        src/Spectre/Renderer.cpp
        src/Spectre/Shader.cpp
        src/Spectre/Texture.cpp
        src/Spectre/VertexArray.cpp
)

target_link_libraries(Spectre glm glfw glad Poltergeist)
