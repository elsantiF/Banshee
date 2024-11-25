cmake_minimum_required(VERSION 3.28)
project(BansheeEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(USE_HYBRID_GRAPHICS "Enable Nvidia Optimus/AMD Hybrid Graphics support" ON)
# if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#     add_compile_options(/W4 /Wall /MP)
#     if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#         add_compile_options(/Zi /Zf)
#     else ()
#         add_compile_options(/O2)
#     endif ()
# endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# TODO: Disable warnings for third party libraries
add_subdirectory(src/ThirdParty)

file(GLOB_RECURSE SOURCES "src/Banshee/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/src/Banshee)
add_executable(BansheeEngine src/Banshee/main.cpp ${SOURCES})

if (USE_HYBRID_GRAPHICS AND WIN32)
    target_compile_definitions(BansheeEngine PRIVATE
            BE_OVER_9000 # Enables Nvidia Optimus/AMD Hybrid Graphics support
    )
endif ()

target_link_libraries(BansheeEngine stb glm assimp::assimp glad glfw imgui)

add_custom_command(TARGET BansheeEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
)
