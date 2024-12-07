project(imgui)

add_library(imgui OBJECT)
file(GLOB IMGUI_FILES "imgui/*.cpp")
target_sources(imgui PRIVATE ${IMGUI_FILES}
        "imgui/backends/imgui_impl_glfw.cpp"
        "imgui/backends/imgui_impl_opengl3.cpp"
)
target_include_directories(imgui SYSTEM PUBLIC imgui)
target_link_libraries(imgui PUBLIC glfw)
