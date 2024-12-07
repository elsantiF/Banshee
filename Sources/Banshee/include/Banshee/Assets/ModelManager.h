#pragma once

#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Spectre/Texture.h>

#include "Banshee/Core/Core.h"
#include "Banshee/Components/StaticMesh.h"
#include "Banshee/Components/Model.h"

#include "Resource.h"
#include "AssetManager.h"
#include "TextureManager.h"

namespace Banshee {
    // TODO: This needs a refactor
    // TODO: I think this is now thread-safe, test it
    class ModelManager final : public ResourceManager<Model> {
        Assimp::Importer m_Importer;
        const aiScene *m_Scene;
        fs::path m_Directory;

        Vector<StaticMesh> m_Meshes;
        Vector<u32> m_Indices;
        Vector<Resource<Texture>> m_Textures;

        void ProcessNode(const aiNode *node, const aiScene *scene);
        void ProcessMesh(const aiMesh *mesh, const aiScene *scene);
        Vector<Resource<Texture>> LoadMaterialTextures(const aiMaterial *mat, aiTextureType type, const String &typeName);

    public:
        ModelManager() = default;

        Resource<Model> Load(const fs::path &modelPath) override;
    };
}
