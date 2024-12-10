module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

export module Banshee.Components.Transform;

import Poltergeist;

export namespace Banshee {
    class Transform {
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Rotation = glm::vec3(0.0f);
        glm::vec3 m_Scale = glm::vec3(1.0f);

        glm::mat4 m_ModelMatrix = glm::identity<glm::mat4>();
        bool m_Dirty = true;

    public:
        [[nodiscard]] glm::mat4 GetModelMatrix();

        Transform &SetPosition(const glm::vec3 &position);
        Transform &SetRotation(const glm::vec3 &rotation);
        Transform &SetScale(const glm::vec3 &scale);

        [[nodiscard]] glm::vec3 &Position() { return m_Position; }
        [[nodiscard]] glm::vec3 &Rotation() { return m_Rotation; }
        [[nodiscard]] glm::vec3 &Scale() { return m_Scale; }

        [[nodiscard]] f32 &PositionX() { return m_Position.x; }
        [[nodiscard]] f32 &PositionY() { return m_Position.y; }
        [[nodiscard]] f32 &PositionZ() { return m_Position.z; }

        [[nodiscard]] f32 &RotationX() { return m_Rotation.x; }
        [[nodiscard]] f32 &RotationY() { return m_Rotation.y; }
        [[nodiscard]] f32 &RotationZ() { return m_Rotation.z; }

        [[nodiscard]] f32 &ScaleX() { return m_Scale.x; }
        [[nodiscard]] f32 &ScaleY() { return m_Scale.y; }
        [[nodiscard]] f32 &ScaleZ() { return m_Scale.z; }

        Transform &Translate(const glm::vec3 &translation);
        Transform &TranslateX(f32 x);
        Transform &TranslateY(f32 y);
        Transform &TranslateZ(f32 z);

        Transform &Scale(const glm::vec3 &scale);
        Transform &Scale(f32 scale);
        Transform &ScaleX(f32 x);
        Transform &ScaleY(f32 y);
        Transform &ScaleZ(f32 z);

        Transform &Rotate(const glm::vec3 &rotation);
        // TODO: Add Quaternion rotation
        Transform &RotateX(f32 x);
        Transform &RotateY(f32 y);
        Transform &RotateZ(f32 z);
    };
}
