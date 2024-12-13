module;
#include <memory>

export module Banshee.World;

import Poltergeist;

export import Banshee.World.Level;

export namespace Banshee {
    class World {
        Ref<Level> m_ActualLevel{};

    public:
        World() = default;

        void SetLevel(const Ref<Level> &level);

        void Tick(f64 delta) const;
        void Render() const;
    };
}
