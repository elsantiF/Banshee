#pragma once

#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Core.h"
#include "Components/StaticMesh.h"
#include "Components/Model.h"
#include "Graphics/Texture.h"
#include "Resource.h"
#include "AssetManager.h"

namespace Banshee {
    // TODO: Make this thread safe
    // This will not be thread safe, use with caution
    class ModelLoader final : public Resource<Model> {
        Assimp::Importer m_Importer;
        const aiScene *m_Scene;
        fs::path m_Directory;

        Vector<Mesh> m_Meshes;
        Vector<u32> m_Indices;
        Vector<Texture> m_Textures;

        void ProcessNode(const aiNode *node, const aiScene *scene);
        void ProcessMesh(const aiMesh *mesh, const aiScene *scene);
        Vector<Texture> LoadMaterialTextures(const aiMaterial *mat, aiTextureType type, const String &typeName);

    public:
        explicit ModelLoader(const fs::path &modelPath);

        void Load(const fs::path &modelPath) override;
    };
}
