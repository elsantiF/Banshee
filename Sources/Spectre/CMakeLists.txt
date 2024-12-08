project(Spectre)

add_library(Spectre STATIC)

target_sources(Spectre PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        Buffer/Buffer.ixx
        Framebuffer/Framebuffer.ixx
        Renderbuffer/Renderbuffer.ixx
        Renderer/Renderer.ixx
        Shader/Shader.ixx
        Texture/Texture.ixx
        Vertex/Vertex.ixx
        VertexArray/VertexArray.ixx

        Spectre.ixx
)

target_sources(Spectre PUBLIC
        Buffer/Buffer.cpp
        Framebuffer/Framebuffer.cpp
        Renderbuffer/Renderbuffer.cpp
        Renderer/Renderer.cpp
        Shader/Shader.cpp
        Texture/Texture.cpp
        VertexArray/VertexArray.cpp
)

target_link_libraries(Spectre glm glfw glad Poltergeist)
