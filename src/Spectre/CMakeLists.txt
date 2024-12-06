project(Spectre)

add_library(Spectre STATIC)
file(GLOB_RECURSE SPECTRE_SOURCES "*.cpp")
target_sources(Spectre PUBLIC ${SPECTRE_SOURCES})
target_include_directories(Spectre INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Spectre glad GSL glfw glm)
