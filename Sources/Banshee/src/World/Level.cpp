#include <imgui.h>
#include <Banshee/Assets/AssetManager.hpp>
#include <Banshee/Core/Application.hpp>
#include <Spectre/Renderer/Renderer.hpp>
#include "Banshee/World/Level.hpp"

namespace Banshee {
    Level::Level() {
        PROFILE_SCOPE();
        auto m_ShaderFramebuffer = AssetManager::GetShaderManager().Get("Resources/Shaders/framebuffer");
        const auto &window = Application::GetInstance()->GetWindow();
        m_Framebuffer = MakeRef<Spectre::Framebuffer>(window->GetSize().first, window->GetSize().second);
        m_Framebuffer->SetShader(m_ShaderFramebuffer);
    }

    void Level::Tick(const f64 delta) {
        PROFILE_SCOPE();
        for (const auto &entity : m_Entity) {
            for (const auto &component : entity->GetComponents()) {
                if (const auto camera = dynamic_cast<Camera *>(component.get())) {
                    camera->SetAspect(static_cast<f32>(m_Framebuffer->GetWidth()) / m_Framebuffer->GetHeight());
                }
                component->OnTick(delta);
            }
        }
    }

    void Level::Render() const {
        PROFILE_SCOPE();
        m_Framebuffer->Bind();
        glEnable(GL_DEPTH_TEST);
        Spectre::Renderer::Clear();

        // Level rendering
        if (m_IsWireframe) {
            Spectre::Renderer::SetPolygonMode(Spectre::PolygonMode::LINE);
        } else {
            Spectre::Renderer::SetPolygonMode(Spectre::PolygonMode::FILL);
        }

        for (const auto &entity : m_Entity) {
            for (const auto &component : entity->GetComponents()) {
                component->OnRender(m_MainCamera.get());
            }
        }

        Spectre::Renderer::SetPolygonMode(Spectre::PolygonMode::FILL);

        m_Framebuffer->Unbind();
        glDisable(GL_DEPTH_TEST);

        // Framebuffer display
        Spectre::Renderer::Clear();
        m_Framebuffer->Draw();
    }

    void Level::ImGui() {
        PROFILE_SCOPE();

        ImGui::Begin("Level");
        for (const auto &entity : m_Entity) {
            ImGui::PushID(entity->GetName().c_str());
            if (ImGui::TreeNode(entity->GetName().c_str())) {
                for (const auto &component : entity->GetComponents()) {
                    ImGui::PushID(component->GetName().c_str());
                    if (ImGui::TreeNode(component->GetName().c_str())) {
                        component->OnImGui();
                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                }
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        ImGui::End();

        OnImGui();
    }
}