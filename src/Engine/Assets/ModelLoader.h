#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Core.h"
#include "Components/Mesh.h"
#include "Components/Model.h"
#include "Graphics/Texture.h"

namespace BansheeEngine {
    // TODO: Make this thread safe
    // This will not be thread safe, use with caution
    class ModelLoader {
        Assimp::Importer m_Importer;
        const aiScene *m_Scene;
        std::string m_Directory;

        Vector<Mesh> m_Meshes;
        Vector<unsigned int> m_Indices;
        Vector<Texture> m_Textures;

        void ProcessNode(const aiNode *node, const aiScene *scene);
        void ProcessMesh(const aiMesh *mesh, const aiScene *scene);
        Vector<Texture> LoadMaterialTextures(const aiMaterial *mat, aiTextureType type, const std::string &typeName);

    public:
        ModelLoader();
        Model LoadModel(const std::string &path);
    };
}
