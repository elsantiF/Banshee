project(glm)

add_library(glm INTERFACE)
file(GLOB GLM_FILES "glm/glm/*.hpp")
target_sources(glm INTERFACE ${GLM_FILES})
target_include_directories(glm SYSTEM INTERFACE glm)
