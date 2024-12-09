project(Poltergeist)

add_library(Poltergeist STATIC)

target_sources(Poltergeist PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        Logger/Logger.ixx
        Container.ixx
        Filesystem.ixx
        Memory.ixx
        Poltergeist.ixx
        String.ixx
        Types.ixx
)

target_sources(Poltergeist PUBLIC
        Logger/Logger.cpp
)

target_link_libraries(Poltergeist fmt::fmt Tracy::TracyClient)
