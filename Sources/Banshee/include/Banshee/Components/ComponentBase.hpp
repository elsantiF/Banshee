#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/World/Entity.hpp>

namespace Banshee {
    class Camera;
}
namespace Banshee {
    class ComponentBase {
        Entity *m_Owner = nullptr;

    protected:
        // This is a temporary solution
        void SetOwner(Entity *owner) { m_Owner = owner; }
        Entity *GetOwner() const { return m_Owner; }

    public:
        ComponentBase() = default;
        virtual ~ComponentBase() = default;

        virtual void OnCreate() = 0;
        virtual void OnTick(f64 delta) = 0;
        virtual void OnRender(Camera *camera) const = 0;
        virtual void OnDestroy() = 0;
        virtual void OnImGui() = 0;

        [[nodiscard]] virtual String GetName() const = 0;

        friend class Entity;
    };
}
