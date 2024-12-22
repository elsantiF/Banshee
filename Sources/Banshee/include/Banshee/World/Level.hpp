#pragma once

#include "Banshee/Components/Camera.hpp"
#include "Spectre/Framebuffer/Framebuffer.hpp"

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/Components/ComponentBase.hpp>

namespace Banshee {
    class World;

    class Level {
        const World *m_World{};
        Vector<Ref<Entity>> m_Entity{};

        // TODO: Below this, all is temporary
        Ref<Spectre::Framebuffer> m_Framebuffer{};
        Ref<Camera> m_MainCamera{};
        bool m_IsWireframe = false;

    public:
        Level();
        virtual ~Level() = default;

        void SetWorld(const World *world) { m_World = world; }
        [[nodiscard]] const World *GetWorld() const { return m_World; }

        Ref<Entity> CreateEntity(const String &name) {
            PROFILE_SCOPE();
            auto entity = MakeRef<Entity>(name);
            m_Entity.push_back(entity);
            return entity;
        }

        void Tick(f64 delta);
        void Render() const;
        void ImGui();

        void SetMainCamera(const Ref<Camera> &camera) { m_MainCamera = camera; }
        [[nodiscard]] const Ref<Camera> &GetMainCamera() const { return m_MainCamera; }

        virtual void OnCreate() = 0;
        virtual void OnDestroy() = 0;
        virtual void OnImGui() = 0;
    };
}
