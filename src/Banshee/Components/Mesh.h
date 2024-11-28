#pragma once

#include <glad/glad.h>

#include "Core/Core.h"
#include "Graphics/Vertex.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace Banshee {
    class Mesh {
        Vector<Vertex> m_Vertices;
        Vector<u32> m_Indices;
        Vector<Texture> m_Textures;

        // TODO: Is really needed to have these here? If mesh is only static perhaps it can use only the VAO
        UniquePtr<VertexArray> m_VAO;
        UniquePtr<Buffer> m_VBO;
        UniquePtr<Buffer> m_EBO;

    public:
        Mesh() = delete;
        Mesh(const Vector<Vertex> &vertices, const Vector<u32> &indices, const Vector<Texture> &textures);
        void Draw(Shader &shader) const;
    };
}
