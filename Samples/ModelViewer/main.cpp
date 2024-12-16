#include <algorithm>
#include <imgui.h>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Profiler/Profiler.hpp>

import Poltergeist;
import Spectre;
import Banshee.Assets.AssetManager;
import Banshee.Assets.ModelManager;
import Banshee.Components.Camera;
import Banshee.Components.Model;
import Banshee.Components.Transform;
import Banshee.Core.Application;
import Banshee.Core.InputManager;
import Banshee.World;

using namespace Banshee;
using namespace Spectre;

class ModelViewer final : public Level {
    Ref<ShaderProgram> m_ShaderMaterial{};
    Ref<ShaderProgram> m_ShaderFramebuffer{};
    Ref<Framebuffer> m_Framebuffer{};
    Ref<Model> m_Model{};
    Ref<Camera> m_Camera{};
    bool m_IsWireframe = false;

    void OnCreate() override {
        PROFILE_SCOPE();
        const auto rootPath = fs::current_path() / "Resources";

        m_ShaderMaterial = AssetManager::GetShaderManager().Get((rootPath / "Shaders/basic").generic_string());
        m_ShaderFramebuffer = AssetManager::GetShaderManager().Get((rootPath / "Shaders/framebuffer").generic_string());

        const auto appInstance = Application::GetInstance();
        const auto &window = appInstance->GetWindow();

        m_Framebuffer = MakeRef<Framebuffer>(window->GetSize().first, window->GetSize().second);
        m_Framebuffer->SetShader(m_ShaderFramebuffer);

        m_Camera = appInstance->GetWorld().AddComponent<Camera>(45.f, window->GetAspect(), 0.1f, 500.f);
        m_Camera->Transform().SetPosition(glm::vec3(0.f, 1.f, 0.f));

        // TODO: Find a better way to do this
        m_Model = AssetManager::GetModelManager().Get(rootPath / "Models/Sponza/sponza.glb");
        m_Model = appInstance->GetWorld().AddComponent<Model>(*m_Model);
    }

    void OnTick(const f64 delta) override {
        PROFILE_SCOPE();
        auto &cameraTransform = m_Camera->Transform();
        const f32 positionSpeed = 10.0f * static_cast<f32>(delta);

        if (InputManager::IsKeyPressed(GLFW_KEY_W)) {
            cameraTransform.Translate(cameraTransform.Forward() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_S)) {
            cameraTransform.Translate(-cameraTransform.Forward() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_D)) {
            cameraTransform.Translate(cameraTransform.Right() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_A)) {
            cameraTransform.Translate(-cameraTransform.Right() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_Q)) {
            cameraTransform.Translate(cameraTransform.Up() * positionSpeed);
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_E)) {
            cameraTransform.Translate(-cameraTransform.Up() * positionSpeed);
        }

        // Rotation update
        const f32 rotationSpeed = 35.0f * static_cast<f32>(delta);

        if (InputManager::IsKeyPressed(GLFW_KEY_DOWN)) {
            cameraTransform.Rotate(glm::vec3(-rotationSpeed, 0.f, 0.f));
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_UP)) {
            cameraTransform.Rotate(glm::vec3(rotationSpeed, 0.f, 0.f));
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_LEFT)) {
            cameraTransform.Rotate(glm::vec3(0.f, rotationSpeed, 0.f));
        }
        if (InputManager::IsKeyPressed(GLFW_KEY_RIGHT)) {
            cameraTransform.Rotate(glm::vec3(0.f, -rotationSpeed, 0.f));
        }

        // TODO: Add this again
        // m_Transform.RotationX() = glm::fclamp(m_Transform.RotationX(), -89.0f, 89.0f);

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_ADD)) {
            m_Camera->Fov() -= 10.f * delta;
        }

        if (InputManager::IsKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
            m_Camera->Fov() += 10.f * delta;
        }

        m_Camera->Fov() = std::clamp(m_Camera->Fov(), 1.0f, 120.0f);
    }

    void OnRender() const override {
        PROFILE_SCOPE();
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
        m_ShaderMaterial->Set("u_MatProjection", m_Camera->GetProjectionMatrix());
        m_ShaderMaterial->Set("u_MatView", m_Camera->GetViewMatrix());
        m_ShaderMaterial->Set("u_LightPosition", glm::vec3(0.f, 0.f, 2.f));

        m_Model->Draw(*m_ShaderMaterial);
        // End of level rendering

        Renderer::SetPolygonMode(PolygonMode::FILL);

        m_Framebuffer->Unbind();
        glDisable(GL_DEPTH_TEST);

        // Framebuffer display
        Renderer::Clear();
        m_Framebuffer->Draw();
    }

    void OnImGUI() override {
        PROFILE_SCOPE();
        ImGui::Begin("Level");
        ImGui::PushID("Camera");
        ImGui::SeparatorText("Camera");
        auto cameraPosition = m_Camera->Transform().GetPosition();
        if (ImGui::InputFloat3("Position", &cameraPosition[0])) {
            m_Camera->Transform().SetPosition(cameraPosition);
        }
        auto cameraRotation = m_Camera->Transform().GetRotationEuler();
        if (ImGui::InputFloat3("Rotation", &cameraRotation[0])) {
            m_Camera->Transform().SetRotation(cameraRotation);
        }
        ImGui::PopID();

        ImGui::PushID("Model");
        ImGui::SeparatorText("Model");
        auto modelPosition = m_Model->Transform().GetPosition();
        if (ImGui::InputFloat3("Position", &modelPosition[0])) {
            m_Model->Transform().SetPosition(modelPosition);
        }
        auto modelRotation = m_Model->Transform().GetRotationEuler();
        if (ImGui::InputFloat3("Rotation", &modelRotation[0])) {
            m_Model->Transform().SetRotation(modelRotation);
        }
        ImGui::PopID();
        ImGui::End();

        ImGui::Begin("Engine");
        ImGui::Text("Delta: %04f ms", Application::GetInstance()->GetDelta() * 1000);

        ImGui::SeparatorText("Render");
        ImGui::Checkbox("Wireframe Render?", &m_IsWireframe);

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
