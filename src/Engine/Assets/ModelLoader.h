#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Core.h"
#include "Components/Mesh.h"
#include "Components/Model.h"
#include "Graphics/Texture.h"

namespace BansheeEngine {
    class ModelLoader {
        static void ProcessNode(const aiNode *node, const aiScene *scene, Vector<Mesh> &meshes, const std::string &directory);
        static Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory);
        static Vector<Texture> LoadMaterialTextures(const aiMaterial *mat, aiTextureType type, const std::string &typeName,
                                                    const std::string &directory);

    public:
        static Model LoadModel(const std::string &path);
    };
}
