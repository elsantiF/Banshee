#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/Components/Component.hpp>
#include <Banshee/Components/Transform.hpp>

namespace Banshee {
    class Entity {
        Vector<Ref<Component>> m_Components{};
        Transform m_Transform{}; // This is temporary, perhaps it will be removed in the future
        String m_Name{};
        bool m_IsActive = true;
    };
}
