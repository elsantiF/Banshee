#pragma once

#include "Core/Core.h"

namespace Banshee {
    template<typename T>
    class Resource {
    protected:
        Ref<T> m_Resource;
        fs::path m_FilePath;

    public:
        Resource() = default;
        virtual ~Resource() = default;

        virtual void Load(const fs::path &filePath) = 0;

        [[nodiscard]] const Ref<T> &GetResource() const {
            return m_Resource;
        }

        [[nodiscard]] const fs::path &GetFilePath() const {
            return m_FilePath;
        }
    };
}
