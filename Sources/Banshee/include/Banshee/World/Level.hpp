#pragma once

#include <memory>

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/Components/Component.hpp>

namespace Banshee {
    class World;

    class Level {
        const World *m_World{};
        Vector<Ref<Component>> m_Components{};

    public:
        Level() = default;

        // This is ugly and I don't know if it will work in any situation
        template <typename T, typename... Args>
            requires std::is_base_of_v<Component, T> && (sizeof...(Args) != 1 || !std::is_same_v<std::decay_t<Args>..., Ref<T>>)
        Ref<T> AddComponent(Args &&...args) {
            m_Components.push_back(MakeRef<T>(std::forward<Args>(args)...));
            return std::static_pointer_cast<T>(m_Components.back());
        }

        template <typename T>
            requires std::is_base_of_v<Component, T>
        void AddComponent(const Ref<T> &component) {
            m_Components.push_back(component);
        }

        void SetWorld(const World *world) { m_World = world; }
        [[nodiscard]] const World *GetWorld() const { return m_World; }

        virtual void OnCreate() = 0;
        virtual void OnDestroy() = 0;
        virtual void OnTick(f64 delta) = 0;
        virtual void OnRender() const = 0;
        virtual void OnImGUI() = 0;
    };
}
