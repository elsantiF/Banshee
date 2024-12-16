module;
#include <filesystem>

export module Banshee.Assets.ShaderManager;

import Poltergeist;
import Spectre.Shader;
import Banshee.Assets.ResourceManager;

export namespace Banshee {
    class ShaderManager final : public ResourceManager<Spectre::ShaderProgram> {
        Ref<Spectre::ShaderProgram> Load(const fs::path &shaderName) override;

    public:
        ShaderManager() = default;
    };
}
