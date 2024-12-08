project(Poltergeist)

add_library(Poltergeist STATIC)

target_sources(Poltergeist PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        Container.ixx
        Filesystem.ixx
        Logger.ixx
        Memory.ixx
        Poltergeist.ixx
        String.ixx
        Types.ixx
)

target_sources(Poltergeist PUBLIC
        Logger.cpp
)

target_link_libraries(Poltergeist fmt::fmt)
