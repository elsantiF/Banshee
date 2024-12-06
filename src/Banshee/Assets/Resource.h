#pragma once

#include "Core/Core.h"

namespace Banshee {
    template<typename T>
    class Resource final {
    protected:
        Ref<T> m_Resource;
        fs::path m_FilePath;

    public:
        Resource(Ref<T> resource, const fs::path &filepath): m_Resource{resource}, m_FilePath{filepath} {};
        ~Resource() = default;

        [[nodiscard]] const Ref<T> &GetResource() const {
            return m_Resource;
        }

        [[nodiscard]] const fs::path &GetFilePath() const {
            return m_FilePath;
        }
    };

    template<typename T>
    class ResourceManager {
    public:
        virtual ~ResourceManager() = default;

    private:
        virtual Resource<T> Load(const fs::path &path) = 0;
    };
}
