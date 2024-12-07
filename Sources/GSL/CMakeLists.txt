project(GSL)

add_library(GSL STATIC)
file(GLOB_RECURSE GSL_SOURCES "src/*.cpp")
target_sources(GSL PUBLIC ${GSL_SOURCES})
target_include_directories(GSL SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(GSL fmt::fmt)
