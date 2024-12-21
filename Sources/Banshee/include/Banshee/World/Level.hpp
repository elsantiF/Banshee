#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/Components/Component.hpp>

namespace Banshee {
    class World;

    class Level {
        const World *m_World{};
        Vector<Ref<Entity>> m_Components{};

    public:
        Level() = default;

        void SetWorld(const World *world) { m_World = world; }
        [[nodiscard]] const World *GetWorld() const { return m_World; }

        Ref<Entity> CreateEntity() {
            PROFILE_SCOPE();
            auto entity = MakeRef<Entity>();
            m_Components.push_back(entity);
            return entity;
        }

        virtual void OnCreate() = 0;
        virtual void OnDestroy() = 0;
        virtual void OnTick(f64 delta) = 0;
        virtual void OnRender() const = 0;
        virtual void OnImGUI() = 0;
    };
}
