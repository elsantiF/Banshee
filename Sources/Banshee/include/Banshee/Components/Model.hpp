#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Spectre/Spectre.hpp>
#include "Component.hpp"
#include "StaticMesh.hpp"
#include "Transform.hpp"

namespace Banshee {
    class Model : public Component {
        Vector<StaticMesh> m_Meshes{};

    public:
        Model() = default;
        explicit Model(Vector<StaticMesh> &meshes);

        void Draw(const Spectre::ShaderProgram &shader);

        Vector<StaticMesh> &GetMeshes() { return m_Meshes; } // TODO: This is only for debug
    };
}
