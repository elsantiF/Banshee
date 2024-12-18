module;
#include <memory>

export module Banshee.World;

import Poltergeist;
import Banshee.Components.Component;
export import Banshee.World.Level;

export namespace Banshee {
    class World {
        Ref<Level> m_ActualLevel{};
        Vector<Ref<Component>> m_Components{};

    public:
        World() = default;

        void SetLevel(const Ref<Level> &level);

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

        void Tick(f64 delta) const;
        void Render() const;
    };
}
