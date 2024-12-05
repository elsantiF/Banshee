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
#include "TextureLoader.h"

namespace Banshee {
    // TODO: This needs a refactor
    // TODO: I think this is now
    class ModelLoader final : public ResourceImporter<Model> {
        Assimp::Importer m_Importer;
        const aiScene *m_Scene;
        fs::path m_Directory;

        Vector<Mesh> m_Meshes;
        Vector<u32> m_Indices;
        Vector<Resource<Texture>> m_Textures;

        void ProcessNode(const aiNode *node, const aiScene *scene);
        void ProcessMesh(const aiMesh *mesh, const aiScene *scene);
        Vector<Resource<Texture>> LoadMaterialTextures(const aiMaterial *mat, aiTextureType type, const String &typeName);

    public:
        ModelLoader() = default;

        Resource<Model> Load(const fs::path &modelPath) override;
    };
}
