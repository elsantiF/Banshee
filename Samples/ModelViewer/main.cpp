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
    Scope<Framebuffer> m_Framebuffer;
    Ref<Model> m_Model;
    Camera m_Camera;
    bool m_IsWireframe = false;

    void OnCreate() override {
        ZoneScoped;
        AssetManager::SetRoot(fs::current_path() / "Resources");
        m_ShaderMaterial = AssetManager::LoadShaderProgram("Shaders/basic").GetResource();
        m_ShaderFramebuffer = AssetManager::LoadShaderProgram("Shaders/framebuffer").GetResource();
        m_Model = ModelManager().Load("Models/Sponza/sponza.glb").GetResource();
        const auto &window = Application::GetInstance()->GetWindow();
        m_Camera = Camera(45.f, window->GetAspect(), 0.1f, 100.f);
        m_Camera.Transform().SetPosition(glm::vec3(0.f, 0.f, 10.f));
        m_Framebuffer = MakeScope<Framebuffer>(window->GetSize().first, window->GetSize().second);
        m_Framebuffer->SetShader(m_ShaderFramebuffer);
    }

    void OnUpdate(const f64 delta) override {
        ZoneScoped;
        m_Camera.Update(delta);
    }

    void OnRender(const f64 delta) override {
        ZoneScoped;
        // Framebuffer begin
        m_Framebuffer->Bind();
        glEnable(GL_DEPTH_TEST);
        Renderer::Clear();

        // Level rendering
        if (m_IsWireframe) {
            Renderer::SetPolygonMode(PolygonMode::LINE);
        } else {
            Renderer::SetPolygonMode(PolygonMode::FILL);
        }

        m_ShaderMaterial->Bind();
        m_ShaderMaterial->SetMat4("u_MatProjection", m_Camera.GetProjectionMatrix());
        m_ShaderMaterial->SetMat4("u_MatView", m_Camera.GetViewMatrix());
        m_ShaderMaterial->SetVec3("u_LightPosition", glm::vec3(0.f, 0.f, 2.f));

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

        ImGui::PushID("Camera");
        ImGui::SeparatorText("Camera");
        ImGui::InputFloat3("Position", &m_Camera.Transform().Position()[0]);
        auto cameraRotation = m_Camera.Transform().RotationEuler();
        if (ImGui::InputFloat3("Rotation", &cameraRotation[0])) {
            m_Camera.Transform().SetRotation(cameraRotation);
        }
        ImGui::PopID();

        ImGui::PushID("Model");
        ImGui::SeparatorText("Model");
        ImGui::InputFloat3("Position", &m_Model->Transform().Position()[0]);
        auto modelRotation = m_Model->Transform().RotationEuler();
        if (ImGui::InputFloat3("Rotation", &modelRotation[0])) {
            m_Model->Transform().SetRotation(modelRotation);
        }
        ImGui::PopID();

        ImGui::SeparatorText("Render");
        ImGui::Checkbox("Wireframe Render?", &m_IsWireframe);

        ImGui::SeparatorText("Memory Debug");
        ImGui::Text("m_Model ref count: %d", m_Model.use_count());

        ImGui::End();
    }
};

int main() {
    Scope<Level> mainLevel = MakeScope<ModelViewer>();
    Application app((std::move(mainLevel)));
    app.Render();
    return 0;
}
