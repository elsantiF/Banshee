project(Banshee)

if (BANSHEE_STATIC)
    add_library(Banshee STATIC)
else ()
    add_library(Banshee SHARED)
endif ()

if (USE_HYBRID_GRAPHICS AND WIN32)
    target_compile_definitions(Banshee PUBLIC
            BE_OVER_9000 # Enables Nvidia Optimus/AMD Hybrid Graphics support
    )
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Banshee PRIVATE
            BE_DEBUG
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Banshee PRIVATE
            BE_RELEASE
    )
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(Banshee PRIVATE /W4 /Wall /Zi /Zf /MDd)
    else ()
        target_compile_options(Banshee PRIVATE -Wall -Wextra -pedantic)
    endif ()
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (MSVC)
        target_compile_options(Banshee PRIVATE /O2)
    else ()
        target_compile_options(Banshee PRIVATE -O2)
    endif ()
endif ()

file(GLOB_RECURSE BANSHEE_SOURCES "*.cpp") # TODO: Change this to only include the necessary files
target_sources(Banshee PUBLIC ${BANSHEE_SOURCES})
target_include_directories(Banshee SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Banshee stb glm assimp::assimp glad glfw imgui GSL)
