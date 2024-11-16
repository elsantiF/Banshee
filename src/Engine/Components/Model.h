#pragma once

#include "Graphics/Mesh.h"
#include "Transform.h"

namespace BansheeEngine {
    class Model {
        std::vector<Mesh> m_Meshes;
        glm::mat4 m_ModelMatrix = glm::identity<glm::mat4>();
        Transform m_Transform;

        void CalculateModelMatrix();

    public:
        Model() = default;
        explicit Model(std::vector<Mesh> &&meshes);

        void Draw(Shader &shader);

        void Translate(const glm::vec3 &translation);
        void Rotate(const glm::vec3 &axis, float angle);
        void Scale(const glm::vec3 &scale);
        void Scale(float scale);
        [[nodiscard]] glm::mat4 GetModelMatrix() const;
    };
}
