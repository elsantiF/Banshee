project(glfw)

add_library(glfw OBJECT)
file(GLOB GLFW_FILES "glfw/src/*.c")
target_sources(glfw PRIVATE ${GLFW_FILES})
target_include_directories(glfw PUBLIC glfw/include)
# TODO: This only works for Windows, need to add support for other platforms but probably changing to SDL before that
target_compile_definitions(glfw PUBLIC -D_GLFW_WIN32)
target_link_libraries(glfw PUBLIC)