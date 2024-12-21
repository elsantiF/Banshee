#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Spectre/Shader/Shader.hpp>
#include "ResourceManager.hpp"

namespace Banshee {
    class ShaderManager final : public ResourceManager<Spectre::ShaderProgram> {
        Ref<Spectre::ShaderProgram> Load(const fs::path &shaderName) override;

    public:
        ShaderManager() = default;
    };
}
