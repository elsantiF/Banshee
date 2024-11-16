#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Core.h"
#include "Components/Mesh.h"
#include "Components/Model.h"

namespace BansheeEngine {
    class ModelLoader {
        static void ProcessNode(const aiNode *node, const aiScene *scene, Vector<Mesh> &meshes);
        static Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

    public:
        static Model LoadModel(const std::string &path);
    };
}
