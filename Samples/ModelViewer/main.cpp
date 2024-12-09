#include <imgui.h>
#include <filesystem>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <tracy/Tracy.hpp>

import Poltergeist;
import Spectre;
import Banshee.Assets.AssetManager;
import Banshee.Assets.ModelManager;
import Banshee.Components.Camera;
import Banshee.Components.Model;
import Banshee.Components.Transform;
import Banshee.Core.Application;
import Banshee.Core.Level;

using namespace Banshee;
using namespace Spectre;

class ModelViewer final : public Level {
    Ref<ShaderProgram> m_ShaderMaterial;
    Ref<ShaderProgram> m_ShaderFramebuffer;
    UniquePtr<Framebuffer> m_Framebuffer;
    Ref<Model> m_Model;
    Camera m_Camera;
    bool m_Wireframe = false;

    void OnCreate() override {
        // TODO: Fix the parent of the parent of the parent path
        AssetManager::SetRoot(fs::current_path().parent_path().parent_path().parent_path() / "Resources");
        m_ShaderMaterial = AssetManager::LoadShaderProgram("Shaders/basic").GetResource();
        m_ShaderFramebuffer = AssetManager::LoadShaderProgram("Shaders/framebuffer").GetResource();
        m_Model = ModelManager().Load("Models/Backpack/backpack.obj").GetResource();
        const auto &window = Application::GetInstance()->GetWindow();
        m_Camera = Camera(45.f, window->GetAspect(), 0.1f, 100.f);
        m_Framebuffer = MakeUnique<Framebuffer>(window->GetSize().first, window->GetSize().second);
        m_Framebuffer->SetShader(m_ShaderFramebuffer);
    }

    void OnUpdate(const f64 delta) override {
        ZoneScoped;
        m_Camera.Update(delta);
        m_Model->GetTransform().RotateY(50.0 * delta);
    }

    void OnRender(const f64 delta) override {
        ZoneScoped;
        // Framebuffer begin
        m_Framebuffer->Bind();
        glEnable(GL_DEPTH_TEST);
        Renderer::Clear();

        // Level rendering
        if (m_Wireframe) {
            Renderer::SetPolygonMode(PolygonMode::LINE);
        } else {
            Renderer::SetPolygonMode(PolygonMode::FILL);
        }

        m_ShaderMaterial->Bind();
        m_ShaderMaterial->SetMat4("u_MatProjection", m_Camera.GetProjectionMatrix());
        m_ShaderMaterial->SetMat4("u_MatView", m_Camera.GetViewMatrix());
        m_ShaderMaterial->SetVec3("u_LightPosition", glm::vec3(1.2f, 1.f, 2.f));

        m_Model->Draw(*m_ShaderMaterial);
        // End of level rendering

        Renderer::SetPolygonMode(PolygonMode::FILL);

        m_Framebuffer->Unbind();
        glDisable(GL_DEPTH_TEST);

        // Framebuffer display
        Renderer::Clear();
        m_Framebuffer->Draw();
    }

    void OnImGUI(const f64 delta) override {
        ZoneScoped;
        ImGui::Begin("Engine");

        ImGui::Text("Delta: %04f ms", delta * 1000);

        ImGui::SeparatorText("Camera");
        const Transform cameraTransform = m_Camera.GetTransform();
        const glm::vec3 cameraPosition = cameraTransform.GetPosition();
        const glm::vec3 cameraRotation = cameraTransform.GetRotation();
        ImGui::Text("Position: X: %04f Y: %04f Z: %04f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        ImGui::Text("Rotation: X: %04f Y: %04f Z: %04f", cameraRotation.x, cameraRotation.y, cameraRotation.z);

        ImGui::SeparatorText("Model");
        const glm::vec3 modelPosition = m_Model->GetTransform().GetPosition();
        const glm::vec3 modelRotation = m_Model->GetTransform().GetRotation();
        ImGui::Text("Position X: %04f Y: %04f Z: %04f", modelPosition.x, modelPosition.y, modelPosition.z);
        ImGui::Text("Rotation X: %04f Y: %04f Z: %04f", modelRotation.x, modelRotation.y, modelRotation.z);

        ImGui::SeparatorText("Render");
        ImGui::Checkbox("Wireframe Render?", &m_Wireframe);

        ImGui::SeparatorText("Memory Debug");
        ImGui::Text("m_Model ref count: %d", m_Model.use_count());

        ImGui::End();
    }
};

int main() {
    UniquePtr<Level> mainLevel = MakeUnique<ModelViewer>();
    Application app((std::move(mainLevel)));
    app.Render();
    return 0;
}
