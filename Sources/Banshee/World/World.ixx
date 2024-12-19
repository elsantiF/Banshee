export module Banshee.World;

import Poltergeist;
import Banshee.Components.Component;
import Banshee.World.Interfaces;
export import Banshee.World.Level;

export namespace Banshee {
    class World : public IWorld {
        Ref<ILevel> m_ActualLevel{};

    public:
        World() = default;
        ~World() override = default;

        void SetLevel(const Ref<ILevel> &level) override;

        [[nodiscard]] ILevel &GetLevel() const override { return *m_ActualLevel; }

        void Tick(f64 delta) const;
        void Render() const;
    };
}
