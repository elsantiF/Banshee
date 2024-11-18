cmake_minimum_required(VERSION 3.28)
project(BansheeEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /Wall /MP)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Zi /Zf)
    else ()
        add_compile_options(/O2)
    endif ()
endif ()

# TODO: Disable warnings for third party libraries
add_subdirectory(src/ThirdParty)

find_package(imgui)
find_package(assimp)
find_package(glfw3)

file(GLOB_RECURSE SOURCES "src/Engine/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/src/Engine)
add_executable(BansheeEngine src/Engine/main.cpp ${SOURCES})

add_subdirectory(src/ThirdParty/imgui)

target_link_libraries(BansheeEngine imgui::imgui assimp::assimp glfw stb glm glad)
