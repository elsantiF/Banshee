#pragma once

#include <glad/glad.h>
#include <Graphics/Texture.h>

#include "Core/Core.h"
#include "Graphics/Vertex.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"
#include "Graphics/Shader.h"

namespace BansheeEngine {
    class Mesh {
        Vector<Vertex> m_Vertices;
        Vector<unsigned int> m_Indices;
        Vector<Texture> m_Textures;

        // TODO: Is really needed to have these here? If mesh is only static perhaps it can use only the VAO
        UniquePtr<VertexArray> m_VAO;
        UniquePtr<Buffer> m_VBO;
        UniquePtr<Buffer> m_EBO;

    public:
        Mesh() = delete;
        Mesh(const Vector<Vertex> &vertices, const Vector<unsigned int> &indices, const Vector<Texture> &textures);
        void Draw(Shader &shader) const;
    };
}
