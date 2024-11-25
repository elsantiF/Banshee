#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BansheeEngine {
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

        [[nodiscard]] glm::vec3 GetPosition() const;
        [[nodiscard]] glm::vec3 GetRotation() const;
        [[nodiscard]] glm::vec3 GetScale() const;

        Transform &Translate(const glm::vec3 &translation);
        Transform &TranslateX(float x);
        Transform &TranslateY(float y);
        Transform &TranslateZ(float z);

        Transform &Scale(const glm::vec3 &scale);
        Transform &Scale(float scale);
        Transform &ScaleX(float x);
        Transform &ScaleY(float y);
        Transform &ScaleZ(float z);

        Transform &Rotate(const glm::vec3 &rotation);
        // TODO: Add Quaternion rotation
        Transform &RotateX(float x);
        Transform &RotateY(float y);
        Transform &RotateZ(float z);
    };
}
