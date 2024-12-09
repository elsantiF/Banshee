project(ModelViewer)

include_directories("../../Thirdparty/tracy")
option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND " " ON)
add_executable(ModelViewer "main.cpp" "../../Thirdparty/tracy/public/TracyClient.cpp")
target_link_libraries(ModelViewer PRIVATE Tracy::TracyClient Banshee)
