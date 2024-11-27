#include "Banshee/Core/Core.h"
#include "Banshee/Core/Application.h"
#include "Banshee/Core/Level.h"
#include "Banshee/Graphics/Shader.h"
#include "Banshee/Components/Model.h"
#include "Banshee/Components/Camera.h"
#include "Banshee/Assets/AssetManager.h"
#include "Banshee/Assets/ModelLoader.h"

using namespace Banshee;

class ModelViewer final : public Level {
    UniquePtr<Shader> m_Shader;
    Model m_Model;
    Camera m_Camera;

    void OnCreate() override {
        AssetManager::SetRoot(fs::current_path().parent_path() / "resources");
        const auto &window = Application::GetInstance()->GetWindow();
        m_Camera = Camera(45.f, window->GetAspect(), 0.1f, 100.f);
        m_Shader = Banshee::MakeUnique<Shader>("shaders/basic");
        m_Model = ModelLoader().LoadModel("models/backpack/backpack.obj");
    }

    void OnUpdate(const double delta) override {
        m_Camera.Update(delta);
    }

    void OnRender(const double delta) override {
        m_Shader->Bind();
        m_Shader->SetMat4("u_MatProjection", m_Camera.GetProjectionMatrix());
        m_Shader->SetMat4("u_MatView", m_Camera.GetViewMatrix());
        m_Shader->SetVec3("u_LightPosition", glm::vec3(1.2f, 1.f, 2.f));

        m_Model.GetTransform().RotateY(50.0 * delta);

        m_Model.Draw(*m_Shader);
    }

    void OnImGUI(const double delta) override {
        ImGui::Begin("Engine");

        ImGui::Text("Delta: %04f ms", delta * 1000);

        ImGui::SeparatorText("Camera");
        const glm::vec3 cameraPosition = m_Camera.GetCameraPosition();
        ImGui::Text("X: %04f Y: %04f Z: %04f", cameraPosition.x, cameraPosition.y, cameraPosition.z);

        ImGui::SeparatorText("Model");
        const glm::vec3 modelPosition = m_Model.GetTransform().GetPosition();
        const glm::vec3 modelRotation = m_Model.GetTransform().GetRotation();
        ImGui::Text("Position X: %04f Y: %04f Z: %04f", modelPosition.x, modelPosition.y, modelPosition.z);
        ImGui::Text("Rotation X: %04f Y: %04f Z: %04f", modelRotation.x, modelRotation.y, modelRotation.z);

        ImGui::SeparatorText("Render");
        if (ImGui::Button("Solid render")) {
            Application::GetInstance()->SetWireframe(false);
        }

        if (ImGui::Button("Wireframe render")) {
            Application::GetInstance()->SetWireframe(true);
        }

        ImGui::End();
    }
};

int main() {
    UniquePtr<Level> mainLevel = MakeUnique<ModelViewer>();
    Application app((std::move(mainLevel)));
    app.Render();
    return 0;
}
