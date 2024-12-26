project(Poltergeist)

add_library(Poltergeist STATIC)

set(POLTERGEIST_INCLUDE_FILES
        include/Poltergeist/Logger/Logger.hpp
        include/Poltergeist/Math/Math.hpp
        include/Poltergeist/Memory/Memory.hpp
        include/Poltergeist/Profiler/Profiler.hpp
        include/Poltergeist/Container.hpp
        include/Poltergeist/Filesystem.hpp
        include/Poltergeist/String.hpp
        include/Poltergeist/Types.hpp

        include/Poltergeist/Poltergeist.hpp
)

set(POLTERGEIST_SOURCE_FILES
        src/Logger/Logger.cpp
        src/Math/Math.cpp
        src/Profiler/Profiler.cpp
)

target_include_directories(Poltergeist
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(Poltergeist
        PRIVATE
        ${POLTERGEIST_SOURCE_FILES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        ${POLTERGEIST_INCLUDE_FILES}
)

target_link_libraries(Poltergeist
        PUBLIC
        glad
        glm::glm
        fmt::fmt
        Tracy::TracyClient
)

install(TARGETS Poltergeist glm
        EXPORT PoltergeistTargets
        FILE_SET HEADERS
)

install(EXPORT PoltergeistTargets
        FILE PoltergeistTargets.cmake
        NAMESPACE Poltergeist::
        DESTINATION lib/cmake/Poltergeist
)