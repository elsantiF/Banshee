#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/World/World.hpp>
#include "Window.hpp"

namespace Banshee {
    class Application {
        inline static Application *s_Instance = nullptr;
        Scope<World> m_World;
        Scope<Window> m_Window;

        f64 m_Delta = 0.0;
        f64 m_LastFrame = 0.0;

    public:
        Application();
        ~Application();

        void SetMainLevel(const Ref<Level> &level) const;

        void Render();

        Scope<Window> &GetWindow();
        static Application *GetInstance();
        [[nodiscard]] f64 GetDelta() const { return m_Delta; }
        [[nodiscard]] World &GetWorld() const { return *m_World; }
    };
}
