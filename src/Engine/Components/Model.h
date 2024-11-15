#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Graphics/Mesh.h"
#include "Core/Logger.h"
#include "Transform.h"

class Model {
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;        // TODO: This should be in the model loader class
    glm::mat4 m_ModelMatrix = glm::identity<glm::mat4>();
    Transform m_Transform;

    void CalculateModelMatrix();

public:
    // TODO: This three functions needs to be in a separated file
    void LoadModel(const std::string &path);
    void ProcessNode(const aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

    void Draw(Shader &shader);

    void Translate(const glm::vec3 &translation);
    void Rotate(const glm::vec3 &axis, float angle);
    void Scale(const glm::vec3 &scale);
    void Scale(float scale);
    [[nodiscard]] glm::mat4 GetModelMatrix() const;
};
