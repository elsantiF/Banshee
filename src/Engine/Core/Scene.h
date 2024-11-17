#pragma once
#include "Application.h"

namespace BansheeEngine {
    class Scene {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        virtual void OnCreate() = 0;
        virtual void OnUpdate(double delta) = 0;
        virtual void OnRender(double delta) = 0;
    };
}
