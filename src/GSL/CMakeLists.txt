project(GSL)

# TODO: Refactor this, do it better, use other rather than INTERFACE
add_library(GSL STATIC)
file(GLOB_RECURSE GSL_SOURCES "*.cpp")
target_sources(GSL PUBLIC ${GSL_SOURCES})
target_include_directories(GSL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GSL fmt::fmt)
