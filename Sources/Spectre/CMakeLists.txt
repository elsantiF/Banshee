project(Spectre)

add_library(Spectre STATIC)

target_sources(Spectre PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        Framebuffer.ixx
        GraphicBuffer.ixx
        Renderbuffer.ixx
        Renderer.ixx
        Shader.ixx
        Spectre.ixx
        Texture.ixx
        Vertex.ixx
        VertexArray.ixx
)

target_sources(Spectre PUBLIC
        Framebuffer.cpp
        GraphicBuffer.cpp
        Renderbuffer.cpp
        Renderer.cpp
        Shader.cpp
        Texture.cpp
        VertexArray.cpp
)

target_link_libraries(Spectre glm glfw glad Poltergeist)
