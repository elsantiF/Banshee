project(Poltergeist)

add_library(Poltergeist STATIC)
file(GLOB_RECURSE POLTERGEIST_SOURCES "src/*.cpp")
target_sources(Poltergeist PUBLIC ${POLTERGEIST_SOURCES})
target_include_directories(Poltergeist SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Poltergeist fmt::fmt)
