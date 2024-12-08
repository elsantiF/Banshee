export module Banshee.Core.Application;

import Poltergeist;
import Banshee.Core.Window;
import Banshee.Core.Level;

export namespace Banshee {
    class Application {
        inline static Application *s_Instance = nullptr;
        UniquePtr<Level> m_ActualLevel;
        UniquePtr<Window> m_Window;

        f64 m_Delta = 0.0;
        f64 m_LastFrame = 0.0;

    public:
        explicit Application(UniquePtr<Level> level);
        ~Application();
        void Render();
        UniquePtr<Window> &GetWindow();
        static Application *GetInstance();
    };
}
