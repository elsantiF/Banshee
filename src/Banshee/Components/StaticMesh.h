#pragma once

#include <glad/glad.h>

#include "Core/Core.h"
#include "Graphics/Vertex.h"
#include "Graphics/VertexArray.h"
#include "Graphics/GraphicBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace Banshee {
    class StaticMesh {
        Vector<Vertex> m_Vertices;
        Vector<u32> m_Indices;
        Vector<Resource<Texture>> m_Textures;
        u32 m_IndexCount{};

        // TODO: Is really needed to have these here? If mesh is only static perhaps it can use only the VAO
        UniquePtr<VertexArray> m_VAO;

    public:
        StaticMesh() = default;
        StaticMesh(const Vector<Vertex> &vertices, const Vector<u32> &indices, const Vector<Resource<Texture>> &textures);
        void Draw(const ShaderProgram &shader) const;

        Vector<Resource<Texture>> &GetTextures() { return m_Textures; } // TODO: This is only for debug
    };
}
