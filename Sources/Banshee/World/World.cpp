module;
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <Profiler/Profiler.hpp>

module Banshee.World;

import Poltergeist;

namespace Banshee {
    void World::SetLevel(const Ref<ILevel> &level) {
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
        m_ActualLevel->OnTick(delta);
    }

    void World::Render() const {
        PROFILE_SCOPE();
        m_ActualLevel->OnRender();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_ActualLevel->OnImGUI();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
