project(Poltergeist)

add_library(Poltergeist STATIC)

target_include_directories(Poltergeist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Poltergeist PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        Logger/Logger.ixx
        Memory/Memory.ixx
        Container.ixx
        Filesystem.ixx
        Poltergeist.ixx
        String.ixx
        Types.ixx
)

target_sources(Poltergeist PUBLIC
        Logger/Logger.cpp
        Profiler/Profiler.cpp
)

target_link_libraries(Poltergeist glad fmt::fmt Tracy::TracyClient)
