module;
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <filesystem>

export module Banshee.Assets.ModelManager;

import Poltergeist;
import Spectre;
import Banshee.Components.StaticMesh;
import Banshee.Components.Model;
import Banshee.Assets.AssetManager;
import Banshee.Assets.Resource;
import Banshee.Assets.TextureManager;

export namespace Banshee {
    // TODO: This needs a refactor
    // TODO: I think this is now thread-safe, test it
    class ModelManager final : public ResourceManager<Model> {
        Assimp::Importer m_Importer;
        const aiScene *m_Scene;
        fs::path m_Directory;

        Vector<StaticMesh> m_Meshes;
        Vector<Resource<Spectre::Texture>> m_Textures;

        void ProcessNode(const aiNode *node, const aiScene *scene, const aiMatrix4x4 &parentTransform);
        void ProcessMesh(const aiMesh *mesh, const aiScene *scene, const aiMatrix4x4 &transform);
        Vector<Resource<Spectre::Texture>> LoadMaterialTextures(const aiMaterial *mat, aiTextureType type, const String &typeName);

    public:
        ModelManager() = default;

        Resource<Model> Load(const fs::path &modelPath) override;
    };
}
