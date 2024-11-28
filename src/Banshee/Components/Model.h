#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Core.h"
#include "Components/Mesh.h"
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

        void Draw(Shader &shader);
    };
}
