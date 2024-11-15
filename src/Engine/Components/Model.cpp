#include "Model.h"

void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Logger::CRITICAL("Error loading model: " + path);
    }

    m_Directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(const aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(ProcessMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};

        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        glm::vec2 uv;
        uv.x = mesh->mTextureCoords[0][i].x;
        uv.y = mesh->mTextureCoords[0][i].y;
        vertex.uv = uv;

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh{vertices, indices};
}

void Model::CalculateModelMatrix() {
    m_ModelMatrix = glm::identity<glm::mat4>();
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_Transform.translation);
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_ModelMatrix = glm::scale(m_ModelMatrix, m_Transform.scale);
}

void Model::Translate(const glm::vec3& translation) {
    m_Transform.translation = translation;
    CalculateModelMatrix();
}

void Model::Rotate(const glm::vec3& axis, const float angle) {
    m_Transform.rotation = axis * angle;
    CalculateModelMatrix();
}

void Model::Scale(const glm::vec3& scale) {
    m_Transform.scale = scale;
    CalculateModelMatrix();
}

void Model::Scale(const float scale) {
    m_Transform.scale = glm::vec3(scale);
    CalculateModelMatrix();
}

glm::mat4 Model::GetModelMatrix() const {
    return m_ModelMatrix;
}

void Model::Draw(Shader &shader) {
    shader.SetMat4Uniform("u_MatModel", m_ModelMatrix);
    for(Mesh &mesh : m_Meshes) {
        mesh.Draw(shader);
    }
}
