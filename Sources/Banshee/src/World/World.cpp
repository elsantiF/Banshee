#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Banshee/World/World.hpp"

namespace Banshee {
    void World::SetLevel(const Ref<Level> &level) {
        PROFILE_SCOPE();
        if (m_ActualLevel) {
            m_ActualLevel->OnDestroy();
        }
        m_ActualLevel = level;
        m_ActualLevel->SetWorld(this);
        m_ActualLevel->OnCreate();
    }

    void World::Tick(const f64 delta) const {
        PROFILE_SCOPE();
        m_ActualLevel->Tick(delta);
    }

    void World::Render() const {
        PROFILE_SCOPE();
        m_ActualLevel->Render();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_ActualLevel->ImGui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
