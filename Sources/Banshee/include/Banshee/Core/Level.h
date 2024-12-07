#pragma once

#include "Core.h"

namespace Banshee {
    class Level {
    public:
        Level() = default;
        virtual ~Level() = default;

        virtual void OnCreate() = 0;
        virtual void OnUpdate(f64 delta) = 0;
        virtual void OnRender(f64 delta) = 0;
        virtual void OnImGUI(f64 delta) = 0;
    };
}
