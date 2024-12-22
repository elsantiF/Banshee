#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Spectre/Spectre.hpp>
#include "ComponentBase.hpp"
#include "StaticMesh.hpp"
#include "Transform.hpp"

namespace Banshee {
    class Model final : public ComponentBase {
        Vector<StaticMesh> m_Meshes{};
        Ref<Transform> m_Transform{};
        Ref<Spectre::ShaderProgram> m_Shader;

    public:
        Model() = default;
        explicit Model(Vector<StaticMesh> &meshes);

        [[nodiscard]] String GetName() const override { return "Model"; }
        void OnCreate() override { m_Transform = GetOwner()->GetComponent<Transform>(); }
        void OnTick(f64 delta) override {}
        void OnRender(Camera *camera) const override;
        void OnDestroy() override {}
        void OnImGui() override {}

        void SetShader(const Ref<Spectre::ShaderProgram> &shader) { m_Shader = shader; }
    };
}
