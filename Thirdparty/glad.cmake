project(glad)

add_library(glad OBJECT)
file(GLOB GLAD_FILES "glad/src/*.c")
target_sources(glad PRIVATE ${GLAD_FILES})
target_include_directories(glad SYSTEM PUBLIC glad/include)
target_link_libraries(glad PRIVATE ${CMAKE_DL_LIBS})
