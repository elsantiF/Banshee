export module Banshee.Core.Application;

import Poltergeist;
import Banshee.Core.Window;
import Banshee.World;

export namespace Banshee {
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
        f64 GetDelta() const { return m_Delta; }
    };
}
