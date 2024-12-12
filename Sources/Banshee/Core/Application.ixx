export module Banshee.Core.Application;

import Poltergeist;
import Banshee.Core.Window;
import Banshee.Core.Level;

export namespace Banshee {
    class Application {
        inline static Application *s_Instance = nullptr;
        Scope<Level> m_ActualLevel;
        Scope<Window> m_Window;

        f64 m_Delta = 0.0;
        f64 m_LastFrame = 0.0;

    public:
        explicit Application(Scope<Level> level);
        ~Application();
        void Render();
        Scope<Window> &GetWindow();
        static Application *GetInstance();
    };
}
