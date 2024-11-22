#include "ModelLoader.h"

// TODO: This needs a refactor
namespace BansheeEngine {
    ModelLoader::ModelLoader() {
        m_Directory = "";
        m_Scene = nullptr;
        m_Meshes.clear();
        m_Indices.clear();
        m_Textures.clear();
    }

    Model ModelLoader::LoadModel(const String &path) {
        const String realPath = AssetManager::GetRoot() + path;
        m_Scene = m_Importer.ReadFile(realPath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode) {
            Logger::CRITICAL("Error loading model: " + path);
        }

        m_Directory = realPath.substr(0, realPath.find_last_of('/')) + "/";
        ProcessNode(m_Scene->mRootNode, m_Scene); // mRootNode can be null, but don't know when

        return Model{std::move(m_Meshes)};
    }

    // Change this, don't use recursion, use something like BFS
    void ModelLoader::ProcessNode(const aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh, scene);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    void ModelLoader::ProcessMesh(const aiMesh *mesh, const aiScene *scene) {
        Vector<Vertex> vertices;
        Vector<unsigned int> indices;
        Vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
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
                vertex.texCoords = texCoords; {
                }
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

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        Vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        Vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        Vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        Vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        m_Meshes.push_back(Mesh(vertices, indices, textures));
    }

    Vector<Texture> ModelLoader::LoadMaterialTextures(const aiMaterial *mat, const aiTextureType type, const String &typeName) {
        Vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool foundTexture = false;

            for (const auto &texture: m_Textures) {
                String filePath = m_Directory + str.C_Str();
                if (std::strcmp(texture.GetFilePath().data(), filePath.c_str()) == 0) {
                    textures.push_back(texture);
                    foundTexture = true;
                    break;
                }
            }

            if (!foundTexture) {
                Texture texture(m_Directory + str.C_Str());
                texture.SetType(typeName);
                textures.push_back(texture);
                m_Textures.push_back(texture);
            }
        }

        return textures;
    }
}
