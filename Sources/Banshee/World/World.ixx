module;
#include <memory>

export module Banshee.World;

import Poltergeist;
export import Banshee.World.Level;
import Banshee.Components.Component;

export namespace Banshee {
    class World {
        Ref<Level> m_ActualLevel{};
        Vector<Ref<Component>> m_Components{};

    public:
        World() = default;

        void SetLevel(const Ref<Level> &level);

        template <typename T, typename... Args>
            requires std::is_base_of_v<Component, T>
        Ref<T> AddComponent(Args &&...args) {
            m_Components.push_back(MakeRef<T>(std::forward<Args>(args)...));
            return std::static_pointer_cast<T>(m_Components.back());
        }

        void Tick(f64 delta) const;
        void Render() const;
    };
}
