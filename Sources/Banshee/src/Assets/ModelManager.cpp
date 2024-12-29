#include <assimp/postprocess.h>
#include <queue>
#include "Banshee/Assets/AssetManager.hpp"
#include "Banshee/Assets/ModelManager.hpp"

// TODO: This needs a refactor
namespace Banshee {
    Ref<Model> ModelManager::Load(const fs::path &modelPath) {
        PROFILE_SCOPE();
        m_Scene = m_Importer.ReadFile(modelPath.generic_string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices |
                                                                      aiProcess_GenNormals | aiProcess_CalcTangentSpace);
        Logger::INFO("Loading model: " + modelPath.generic_string());

        if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode) {
            Logger::CRITICAL("Error loading model: " + modelPath.generic_string());
        }

        const aiMatrix4x4 identity;
        m_Directory = modelPath.parent_path();
        ProcessNode(m_Scene->mRootNode, m_Scene, identity); // mRootNode can be null, but don't know when

        const auto m_Resource = MakeRef<Model>(m_Meshes);

        return m_Resource;
    }
    
    void ModelManager::ProcessNode(const aiNode *node, const aiScene *scene, const aiMatrix4x4 &parentTransform) {
        PROFILE_SCOPE();
        std::queue<Pair<const aiNode *, aiMatrix4x4>> nodeQueue;
        nodeQueue.emplace(node, parentTransform);

        while (!nodeQueue.empty()) {
            auto [node, parentTransform] = nodeQueue.front();
            nodeQueue.pop();

            const aiMatrix4x4 transform = parentTransform * node->mTransformation;

            for (u32 i = 0; i < node->mNumMeshes; i++) {
                const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                ProcessMesh(mesh, scene, transform);
            }

            for (u32 i = 0; i < node->mNumChildren; i++) {
                nodeQueue.emplace(node->mChildren[i], transform);
            }
        }
    }

    // This is stolen from Overload, pretty code
    void ModelManager::ProcessMesh(const aiMesh *mesh, const aiScene *scene, const aiMatrix4x4 &transform) {
        PROFILE_SCOPE();
        Vector<Spectre::Vertex> vertices;
        Vector<u32> indices;
        Vector<Ref<Spectre::Texture>> texturesResources;

        vertices.reserve(mesh->mNumVertices);
        indices.reserve(mesh->mNumFaces * 3);

        for (u32 i = 0; i < mesh->mNumVertices; i++) {
            aiVector3f position = transform * mesh->mVertices[i];
            aiVector3f normal = transform * (mesh->mNormals ? mesh->mNormals[i] : aiVector3f(0.f));
            aiVector3f texCoords = (mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i] : aiVector3f(0.f));
            aiVector3f tangent = transform * (mesh->mTangents ? mesh->mTangents[i] : aiVector3f(0.f));
            aiVector3f bitangent = transform * (mesh->mBitangents ? mesh->mBitangents[i] : aiVector3f(0.f));

            vertices.push_back({
                {position.x, position.y, position.z},
                {normal.x, normal.y, normal.z},
                {texCoords.x, texCoords.y},
                {tangent.x, tangent.y, tangent.z},
                {bitangent.x, bitangent.y, bitangent.z}
            });
        }

        for (u32 faceID = 0; faceID < mesh->mNumFaces; faceID++) {
            const auto &face = mesh->mFaces[faceID];

            if (face.mNumIndices != 3) {
                Logger::CRITICAL("Face is not a triangle");
            }

            for (u32 indexID = 0; indexID < 3; indexID++) {
                indices.push_back(face.mIndices[indexID]);
            }
        }

        const aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        Vector<Ref<Spectre::Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        Vector<Ref<Spectre::Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        Vector<Ref<Spectre::Texture>> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        Vector<Ref<Spectre::Texture>> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");

        texturesResources.insert(texturesResources.end(), diffuseMaps.begin(), diffuseMaps.end());
        texturesResources.insert(texturesResources.end(), specularMaps.begin(), specularMaps.end());
        texturesResources.insert(texturesResources.end(), normalMaps.begin(), normalMaps.end());
        texturesResources.insert(texturesResources.end(), heightMaps.begin(), heightMaps.end());

        m_Meshes.emplace_back(vertices, indices, texturesResources);
    }

    Vector<Ref<Spectre::Texture>> ModelManager::LoadMaterialTextures(const aiMaterial *mat, const aiTextureType type, const String &typeName) {
        PROFILE_SCOPE();
        Vector<Ref<Spectre::Texture>> textures;
        const u32 textureCount = mat->GetTextureCount(type);
        textures.reserve(textureCount);

        for (u32 i = 0; i < textureCount; i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            fs::path filePath = m_Directory / str.C_Str();

            auto texture = AssetManager::GetTextureManager().Get(filePath);

            textures.push_back(texture);
            m_Textures.push_back(texture);
        }

        return textures;
    }
}
