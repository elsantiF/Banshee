project(glad)

add_library(glad STATIC glad/src/glad.c)

target_include_directories(glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glad/include>
        $<INSTALL_INTERFACE:include/glad>
)

target_link_libraries(glad PRIVATE ${CMAKE_DL_LIBS})

install(TARGETS glad
        EXPORT gladTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include/glad
)

install(DIRECTORY glad/include/ DESTINATION include/glad)

install(EXPORT gladTargets
        FILE gladConfig.cmake
        NAMESPACE glad::
        DESTINATION lib/cmake/glad
)
