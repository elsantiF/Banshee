project(ModelViewer)

add_executable(ModelViewer
        CameraController.cpp
        main.cpp
)

target_link_libraries(ModelViewer Banshee imgui)
