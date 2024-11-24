#include "Core/Core.h"
#include "Core/Application.h"
#include "Core/Scene.h"
#include "Graphics/Shader.h"
#include "Components/Model.h"
#include "Components/Camera.h"
#include "Assets/AssetManager.h"
#include "Assets/ModelLoader.h"

using namespace BansheeEngine;

class ModelViewer final : public Scene {
    UniquePtr<Shader> m_Shader;
    Model m_Model;
    Camera m_Camera;

    void OnCreate() override {
        AssetManager::SetRoot(fs::current_path() / "resources");
        const auto &window = Application::GetInstance()->GetWindow();
        // TODO: Retrieve the aspect from the window
        m_Camera = Camera(45.f, window->GetAspect(), 0.1f, 100.f);
        m_Shader = BansheeEngine::MakeUnique<Shader>("shaders/basic");
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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Engine");

        ImGui::Text("Delta: %04f ms", delta * 1000);

        ImGui::SeparatorText("Camera");
        glm::vec3 cameraPosition = m_Camera.GetCameraPosition();
        ImGui::Text("X: %04f Y: %04f Z: %04f", cameraPosition.x, cameraPosition.y, cameraPosition.z);

        ImGui::SeparatorText("Render");
        if (ImGui::Button("Solid render")) {
            Renderer::SetPolygonMode(PolygonMode::FILL);
        }

        if (ImGui::Button("Wireframe render")) {
            Renderer::SetPolygonMode(PolygonMode::LINE);
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};

int main() {
    UniquePtr<Scene> mainScene = MakeUnique<ModelViewer>();
    Application app((std::move(mainScene)));
    app.Render();
    return 0;
}
