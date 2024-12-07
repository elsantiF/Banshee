project(Spectre)

add_library(Spectre STATIC)
file(GLOB_RECURSE SPECTRE_SOURCES "src/*.cpp")
target_sources(Spectre PUBLIC ${SPECTRE_SOURCES})
target_include_directories(Spectre SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Spectre glad GSL glfw glm)
