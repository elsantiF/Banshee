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
        m_Scene = m_Importer.ReadFile(realPath.generic_string(), aiProcess_Triangulate | aiProcess_FlipUVs);
        Logger::INFO("Loading model: " + modelPath.generic_string());

        if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode) {
            Logger::CRITICAL("Error loading model: " + modelPath.generic_string());
        }

        m_Directory = realPath.parent_path();
        ProcessNode(m_Scene->mRootNode, m_Scene); // mRootNode can be null, but don't know when

        const auto m_Resource = MakeRef<Model>(Model{std::move(m_Meshes)});

        return Resource<Model>{m_Resource, realPath};
    }

    // Change this, don't use recursion, use something like BFS
    void ModelManager::ProcessNode(const aiNode *node, const aiScene *scene) {
        ZoneScoped;
        for (u32 i = 0; i < node->mNumMeshes; i++) {
            const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh, scene);
        }

        for (u32 i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    void ModelManager::ProcessMesh(const aiMesh *mesh, const aiScene *scene) {
        ZoneScoped;
        Vector<Vertex> vertices;
        Vector<u32> indices;
        Vector<Resource<Texture>> texturesResources;

        for (u32 i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;

            if (mesh->HasNormals()) {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }

            if (mesh->HasTextureCoords(0)) {
                glm::vec2 texCoords;
                texCoords.x = mesh->mTextureCoords[0][i].x;
                texCoords.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoords = texCoords;
            }

            if (mesh->HasTangentsAndBitangents()) {
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.tangent = vector;

                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.bitangent = vector;
            }

            vertices.push_back(vertex);
        }

        for (u32 i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (u32 j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
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
