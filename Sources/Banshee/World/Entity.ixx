export module Banshee.World.Entity;

import Poltergeist;
import Banshee.Components.Component;
import Banshee.Components.Transform;

export namespace Banshee {
    class Entity {
        Vector<Ref<Component>> m_Components{};
        Transform m_Transform{}; // This is temporary, perhaps it will be removed in the future
        String m_Name{};
        bool m_IsActive = true;
    };
}
