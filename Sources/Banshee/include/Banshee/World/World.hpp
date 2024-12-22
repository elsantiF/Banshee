#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/Components/ComponentBase.hpp>
#include "Level.hpp"

namespace Banshee {
    class World {
        Ref<Level> m_ActualLevel{};

    public:
        World() = default;

        void SetLevel(const Ref<Level> &level);

        [[nodiscard]] Level &GetLevel() const { return *m_ActualLevel; }

        void Tick(f64 delta) const;
        void Render() const;
    };
}
