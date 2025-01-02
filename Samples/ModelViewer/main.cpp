#include <imgui.h>
#include <Poltergeist/Poltergeist.hpp>
#include <Spectre/Spectre.hpp>
#include <Banshee/Banshee.hpp>
#include "CameraController.h"

using namespace Banshee;
using namespace Spectre;

class ModelViewer final : public Level {
    Ref<ShaderProgram> m_ShaderMaterial{};
    Ref<Entity> m_Model{};
    Ref<Entity> m_Camera{};

    void OnCreate() override {
        PROFILE_SCOPE();
        const auto rootPath = fs::current_path() / "Resources";

        m_ShaderMaterial = AssetManager::GetShaderManager().Get((rootPath / "Shaders/basic").generic_string());

        m_Camera = CreateEntity("Camera");
        m_Camera->AddComponent<Transform>()->SetPosition(glm::vec3(0.f, 1.f, 0.f));
        m_Camera->AddComponent<Camera>(45.f, 0.1f, 500.f);
        m_Camera->AddComponent<CameraController>();
        SetMainCamera(m_Camera->GetComponent<Camera>());

        m_Model = CreateEntity("Model");
        m_Model->AddComponent<Transform>();
        m_Model->AddComponent<Model>(AssetManager::GetModelManager().Get(rootPath / "Models/Sponza/sponza.glb"));
        m_Model->GetComponent<Model>()->SetShader(m_ShaderMaterial);
    }

    void OnImGui() override {
        PROFILE_SCOPE();
        ImGui::Begin("Engine");
        ImGui::Text("Last Delta: %.4f ms", Application::GetInstance()->GetDelta() * 1000);
        ImGui::Text("Average FPS: %.2f", Application::GetInstance()->GetAvgFPS());

        //ImGui::SeparatorText("Render");
        //ImGui::Checkbox("Wireframe Render?", &m_IsWireframe);

        ImGui::SeparatorText("Memory Debug");
        ImGui::Text("m_Camera ref count: %ld", m_Camera.use_count());
        ImGui::Text("m_Model ref count: %ld", m_Model.use_count());
        ImGui::End();

        ImGui::Begin("Loaded Resources");
        ImGui::SeparatorText("Models");
        for (const auto &[path, resource] : AssetManager::GetModelManager().GetAllLoadedResources()) {
            ImGui::Text("%s: %ld", path.filename().string().c_str(), resource.use_count());
        }

        ImGui::SeparatorText("Textures");
        for (const auto &[path, resource] : AssetManager::GetTextureManager().GetAllLoadedResources()) {
            ImGui::Text("%s: %ld", path.filename().string().c_str(), resource.use_count());
        }

        ImGui::SeparatorText("Shaders");
        for (const auto &[path, resource] : AssetManager::GetShaderManager().GetAllLoadedResources()) {
            ImGui::Text("%s: %ld", path.filename().string().c_str(), resource.use_count());
        }
        ImGui::End();
    }

    void OnDestroy() override {
        // Do nothing for now
        return;
    }
};

int main() {
    Application app;
    app.SetMainLevel(MakeRef<ModelViewer>());
    app.Render();
    return 0;
}
