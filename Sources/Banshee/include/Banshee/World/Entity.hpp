#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/Components/Component.hpp>

namespace Banshee {
    class Component;

    class Entity {
        Vector<Ref<Component>> m_Components{};
        String m_Name{};
        bool m_IsActive = true;

    public:
        // This is ugly and I don't know if it will work in any situation
        template <typename T, typename... Args>
            requires std::is_base_of_v<Component, T> && (sizeof...(Args) != 1 || !std::is_same_v<std::decay_t<Args>..., Ref<T>>)
        Ref<T> AddComponent(Args &&...args) {
            PROFILE_SCOPE();
            auto component = MakeRef<T>(std::forward<Args>(args)...);
            component->SetOwner(this);
            m_Components.push_back(component);
            return std::static_pointer_cast<T>(m_Components.back());
        }

        template <typename T>
            requires std::is_base_of_v<Component, T>
        void AddComponent(const Ref<T> &component) {
            PROFILE_SCOPE();
            component->SetOwner(this);
            m_Components.push_back(component);
        }

        template <typename T>
            requires std::is_base_of_v<Component, T>
        [[nodiscard]] Ref<T> GetComponent() const {
            PROFILE_SCOPE();
            for (const auto &component : m_Components) {
                if (std::dynamic_pointer_cast<T>(component)) {
                    return std::static_pointer_cast<T>(component);
                }
            }

            return nullptr;
        }
    };
}
