export module Banshee.World.Level;

import Poltergeist;

export namespace Banshee {
    class World;

    class Level {
        World *m_World = nullptr;

        void SetWorld(World *world) { m_World = world; }
    public:
        Level() = default;
        virtual ~Level() = default;

        virtual void OnCreate() = 0;
        virtual void OnTick(f64 delta) = 0;
        virtual void OnRender() = 0;
        virtual void OnImGUI() = 0;
        virtual void OnDestroy() = 0;

        [[nodiscard]] World &GetWorld() const { return *m_World; }

        friend class World;
    };
}
