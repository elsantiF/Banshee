module;
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <tracy/Tracy.hpp>

module Banshee.Assets.ModelManager;

// TODO: This needs a refactor
namespace Banshee {
    Resource<Model> ModelManager::Load(const fs::path &modelPath) {
        ZoneScoped;
        const fs::path realPath = AssetManager::GetRoot() / modelPath;
        m_Scene = m_Importer.ReadFile(realPath.generic_string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices |
                                                                     aiProcess_GenNormals | aiProcess_CalcTangentSpace);
        Logger::INFO("Loading model: " + modelPath.generic_string());

        if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode) {
            Logger::CRITICAL("Error loading model: " + modelPath.generic_string());
        }

        const aiMatrix4x4 identity;
        m_Directory = realPath.parent_path();
        ProcessNode(m_Scene->mRootNode, m_Scene, identity); // mRootNode can be null, but don't know when

        const auto m_Resource = MakeRef<Model>(Model{std::move(m_Meshes)});

        return Resource<Model>{m_Resource, realPath};
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
        Vector<Vertex> vertices;
        Vector<u32> indices;
        Vector<Resource<Texture>> texturesResources;

        for (u32 i = 0; i < mesh->mNumVertices; i++) {
            aiVector3f position = transform * mesh->mVertices[i];
            aiVector3f normal = transform * ((mesh->mNormals) ? mesh->mNormals[i] : aiVector3f(0.f));
            aiVector3f texCoords = transform * ((mesh->mTextureCoords[0]) ? mesh->mTextureCoords[0][i] : aiVector3f(0.f));
            aiVector3f tangent = transform * ((mesh->mTangents) ? mesh->mTangents[i] : aiVector3f(0.f));
            aiVector3f bitangent = transform * ((mesh->mBitangents) ? mesh->mBitangents[i] : aiVector3f(0.f));

            vertices.push_back(Vertex{
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

        Vector<Resource<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        Vector<Resource<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        Vector<Resource<Texture>> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        Vector<Resource<Texture>> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");

        texturesResources.insert(texturesResources.end(), diffuseMaps.begin(), diffuseMaps.end());
        texturesResources.insert(texturesResources.end(), specularMaps.begin(), specularMaps.end());
        texturesResources.insert(texturesResources.end(), normalMaps.begin(), normalMaps.end());
        texturesResources.insert(texturesResources.end(), heightMaps.begin(), heightMaps.end());

        m_Meshes.emplace_back(vertices, indices, texturesResources);
    }

    Vector<Resource<Texture>> ModelManager::LoadMaterialTextures(const aiMaterial *mat, const aiTextureType type, const String &typeName) {
        ZoneScoped;
        Vector<Resource<Texture>> textures;
        for (u32 i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool foundTexture = false;
            fs::path filePath = m_Directory / str.C_Str();

            for (const auto &texture : m_Textures) {
                if (texture.GetFilePath() == filePath) {
                    textures.push_back(texture);
                    foundTexture = true;
                    break;
                }
            }

            if (!foundTexture) {
                auto texture = TextureManager().Load(filePath);

                textures.push_back(texture);
                m_Textures.push_back(texture);
            }
        }

        return textures;
    }
}
