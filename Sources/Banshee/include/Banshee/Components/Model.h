#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Banshee/Core/Core.h"
#include "Banshee/Components/StaticMesh.h"
#include "Transform.h"

namespace Banshee {
    class Model {
        Vector<StaticMesh> m_Meshes;
        Transform m_Transform;

        void CalculateModelMatrix();

    public:
        Model() = default;
        explicit Model(Vector<StaticMesh> &&meshes);

        Transform &GetTransform();

        void Draw(const ShaderProgram &shader);

        Vector<StaticMesh> &GetMeshes() { return m_Meshes; } // TODO: This is only for debug
    };
}
