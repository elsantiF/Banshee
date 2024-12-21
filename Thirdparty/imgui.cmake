project(imgui)

add_library(imgui STATIC)

file(GLOB IMGUI_FILES "imgui/*.cpp")
file(GLOB IMGUI_HEADERS "imgui/*.h")

target_sources(imgui
        PRIVATE ${IMGUI_FILES} "imgui/backends/imgui_impl_glfw.cpp" "imgui/backends/imgui_impl_opengl3.cpp"
        PUBLIC FILE_SET HEADERS BASE_DIRS imgui
        FILES ${IMGUI_HEADERS}
)

target_include_directories(imgui PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/>
        $<INSTALL_INTERFACE:include/imgui>
)

target_link_libraries(imgui PRIVATE ${CMAKE_DL_LIBS} glfw)

install(TARGETS imgui glfw
        EXPORT imguiTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        FILE_SET HEADERS
)

install(EXPORT imguiTargets
        FILE imguiConfig.cmake
        NAMESPACE imgui::
        DESTINATION lib/cmake/imgui
)
