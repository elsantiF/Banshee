project(stb)

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stb/>
        $<INSTALL_INTERFACE:include/stb>
)

install(TARGETS stb
        EXPORT stbTargets
        INCLUDES DESTINATION include/stb
)

install(DIRECTORY stb/ DESTINATION include/stb)

install(EXPORT stbTargets
        FILE stbConfig.cmake
        NAMESPACE stb::
        DESTINATION lib/cmake/stb
)
