module;
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <tracy/Tracy.hpp>

module Banshee.World;

import Poltergeist;

namespace Banshee {
    void World::SetLevel(const Ref<Level> &level) {
        ZoneScoped;
        if (m_ActualLevel) {
            m_ActualLevel->OnDestroy();
        }
        m_ActualLevel = level;
        m_ActualLevel->OnCreate();
    }

    void World::Tick(const f64 delta) const {
        ZoneScoped;
        m_ActualLevel->OnTick(delta);
    }

    void World::Render() const {
        ZoneScoped;
        m_ActualLevel->OnRender();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_ActualLevel->OnImGUI();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
