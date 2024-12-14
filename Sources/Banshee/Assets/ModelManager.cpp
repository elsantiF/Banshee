module;
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <tracy/Tracy.hpp>

module Banshee.Assets.ModelManager;

import Banshee.Assets.AssetManager;

// TODO: This needs a refactor
namespace Banshee {
    Ref<Model> ModelManager::Load(const fs::path &modelPath) {
        ZoneScoped;
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

    // Change this, don't use recursion, use something like BFS
    void ModelManager::ProcessNode(const aiNode *node, const aiScene *scene, const aiMatrix4x4 &parentTransform) {
        ZoneScoped;
        const aiMatrix4x4 transform = parentTransform * node->mTransformation;
        for (u32 i = 0; i < node->mNumMeshes; i++) {
            const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh, scene, transform);
        }

        for (u32 i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, transform);
        }
    }

    // This is stolen from Overload, pretty code
    void ModelManager::ProcessMesh(const aiMesh *mesh, const aiScene *scene, const aiMatrix4x4 &transform) {
        ZoneScoped;
        Vector<Spectre::Vertex> vertices;
        Vector<u32> indices;
        Vector<Ref<Spectre::Texture>> texturesResources;

        for (u32 i = 0; i < mesh->mNumVertices; i++) {
            aiVector3f position = transform * mesh->mVertices[i];
            aiVector3f normal = transform * ((mesh->mNormals) ? mesh->mNormals[i] : aiVector3f(0.f));
            aiVector3f texCoords = ((mesh->mTextureCoords[0]) ? mesh->mTextureCoords[0][i] : aiVector3f(0.f));
            aiVector3f tangent = transform * ((mesh->mTangents) ? mesh->mTangents[i] : aiVector3f(0.f));
            aiVector3f bitangent = transform * ((mesh->mBitangents) ? mesh->mBitangents[i] : aiVector3f(0.f));

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

            for (u32 indexID = 0; indexID < face.mNumIndices; indexID++) {
                indices.push_back(face.mIndices[indexID]);
            }
        }

        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

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
        ZoneScoped;
        Vector<Ref<Spectre::Texture>> textures;

        for (u32 i = 0; i < mat->GetTextureCount(type); i++) {
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
