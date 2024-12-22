#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Banshee/Components/ComponentBase.hpp>

namespace Banshee {
    class ComponentBase;

    class Entity {
        Vector<Ref<ComponentBase>> m_Components{};
        String m_Name{};
        bool m_IsActive = true;

    public:
        explicit Entity(const String &name) : m_Name{name} {}

        // This is ugly and I don't know if it will work in any situation
        template <typename T, typename... Args>
            requires std::is_base_of_v<ComponentBase, T> && (sizeof...(Args) != 1 || !std::is_same_v<std::decay_t<Args>..., Ref<T>>)
        Ref<T> AddComponent(Args &&...args) {
            PROFILE_SCOPE();
            auto component = MakeRef<T>(std::forward<Args>(args)...);
            component->SetOwner(this);
            component->OnCreate();
            m_Components.push_back(component);
            return std::static_pointer_cast<T>(m_Components.back());
        }

        template <typename T>
            requires std::is_base_of_v<ComponentBase, T>
        void AddComponent(const Ref<T> &component) {
            PROFILE_SCOPE();
            component->SetOwner(this);
            component->OnCreate();
            m_Components.push_back(component);
        }

        template <typename T>
            requires std::is_base_of_v<ComponentBase, T>
        [[nodiscard]] Ref<T> GetComponent() const {
            PROFILE_SCOPE();
            for (const auto &component : m_Components) {
                if (std::dynamic_pointer_cast<T>(component)) {
                    return std::static_pointer_cast<T>(component);
                }
            }

            return nullptr;
        }

        [[nodiscard]] String GetName() const { return m_Name; }

        void SetActive(const bool active) { m_IsActive = active; }
        [[nodiscard]] bool IsActive() const { return m_IsActive; }

        Vector<Ref<ComponentBase>> &GetComponents() { return m_Components; }
    };
}
