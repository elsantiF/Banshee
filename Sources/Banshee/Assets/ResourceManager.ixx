module;
#include <filesystem>
#include <tracy/Tracy.hpp>

export module Banshee.Assets.ResourceManager;

import Poltergeist;

export namespace Banshee {
    template <typename Resource>
    class ResourceManager {
    protected:
        UnorderedMap<fs::path, Ref<Resource>> m_Resources;

    public:
        ResourceManager() = default;
        virtual ~ResourceManager() = default;

        virtual Ref<Resource> Load(const fs::path &path) = 0;

        Ref<Resource> Get(const fs::path &path) {
            ZoneScoped;
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
            ZoneScoped;
            auto it = m_Resources.find(path);
            if (it != m_Resources.end()) {
                m_Resources.erase(it);
            }
        }

        void UnloadAll() {
            ZoneScoped;
            m_Resources.clear();
        }
    };
}
