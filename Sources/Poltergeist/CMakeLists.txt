project(Poltergeist)

add_library(Poltergeist STATIC)

target_sources(Poltergeist PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        include/Poltergeist/Container.ixx
        include/Poltergeist/Filesystem.ixx
        include/Poltergeist/Logger.ixx
        include/Poltergeist/Memory.ixx
        include/Poltergeist/Poltergeist.ixx
        include/Poltergeist/String.ixx
        include/Poltergeist/Types.ixx
)

target_sources(Poltergeist PUBLIC
        src/Poltergeist/Logger.cpp
)

target_link_libraries(Poltergeist fmt::fmt)
