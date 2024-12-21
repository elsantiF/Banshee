#pragma once

#include <Poltergeist/Poltergeist.hpp>

namespace Banshee {
    template <typename Resource>
    class ResourceManager {
    protected:
        UnorderedMap<fs::path, Ref<Resource>> m_Resources;

        virtual Ref<Resource> Load(const fs::path &path) = 0;

    public:
        ResourceManager() = default;
        virtual ~ResourceManager() = default;

        Ref<Resource> Get(const fs::path &path) {
            PROFILE_SCOPE();
            auto it = m_Resources.find(path);
            if (it != m_Resources.end()) {
                return it->second;
            }

            auto resource = Load(path);
            if (resource) {
                m_Resources[path] = resource;
                return resource;
            }

            Logger::CRITICAL("Can't find resource: " + path.string());
            return nullptr;
        }

        void Unload(const fs::path &path) {
            PROFILE_SCOPE();
            auto it = m_Resources.find(path);
            if (it != m_Resources.end()) {
                m_Resources.erase(it);
            }
        }

        void UnloadAll() {
            PROFILE_SCOPE();
            m_Resources.clear();
        }

        // IMPORTANT: This is only intended for debugging purposes
        UnorderedMap<fs::path, Ref<Resource>> &GetAllLoadedResources() { return m_Resources; }
    };
}
