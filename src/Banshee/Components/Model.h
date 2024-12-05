#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Core.h"
#include "Components/StaticMesh.h"
#include "Transform.h"

namespace Banshee {
    class Model {
        Vector<Mesh> m_Meshes;
        Transform m_Transform;

        void CalculateModelMatrix();

    public:
        Model() = default;
        explicit Model(Vector<Mesh> &&meshes);

        Transform &GetTransform();

        void Draw(const ShaderProgram &shader);

        Vector<Mesh> &GetMeshes() { return m_Meshes; } // TODO: This is only for debug
    };
}
