export module Banshee.World.Level;

import Poltergeist;

export namespace Banshee {
    class Level {
    public:
        Level() = default;
        virtual ~Level() = default;

        virtual void OnCreate() = 0;
        virtual void OnTick(f64 delta) = 0;
        virtual void OnRender() const = 0;
        virtual void OnImGUI() = 0;
        virtual void OnDestroy() = 0;

        // TODO: Add a way to get the world
    };
}
