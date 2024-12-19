// This file only exist to avoid circular dependencies between World and Level
export module Banshee.World.Interfaces;

import Poltergeist;

export namespace Banshee {
    class IWorld;

    class ILevel {
    public:
        ILevel() = default;
        virtual ~ILevel() = default;

        virtual void OnCreate() = 0;
        virtual void OnTick(f64 delta) = 0;
        virtual void OnRender() const = 0;
        virtual void OnImGUI() = 0;
        virtual void OnDestroy() = 0;

        virtual void SetWorld(const IWorld *world) = 0;
        [[nodiscard]] virtual const IWorld *GetWorld() const = 0;
    };

    class IWorld {
    public:
        IWorld() = default;
        virtual ~IWorld() = default;

        virtual void SetLevel(const Ref<ILevel> &level) = 0;
        [[nodiscard]] virtual ILevel &GetLevel() const = 0;
    };
}
