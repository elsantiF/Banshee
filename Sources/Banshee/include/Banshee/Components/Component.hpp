#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/World/Entity.hpp>

namespace Banshee {
    class Component {
        u64 m_ComponentID = 0;  // TODO: Not used yet
        bool m_IsActive = true; // TODO: Not used yet
        Entity *m_Owner = nullptr;

    public:
        // This is a temporary solution
        void SetOwner(Entity *owner) { m_Owner = owner; }
        Entity *GetOwner() const { return m_Owner; }

        virtual void OnUpdate(const f64 delta) {};
    };
}
