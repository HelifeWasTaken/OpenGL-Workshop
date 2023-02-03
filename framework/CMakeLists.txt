include(FetchContent)

# GLAD - OpenGL Loader
add_subdirectory(glad)

# GLFW - Windowing Library
FetchContent_Declare(glfw
    URL https://github.com/glfw/glfw/releases/download/3.3.3/glfw-3.3.3.zip
    URL_HASH SHA1=f9f0e1f515040e3c41d072d63ff31db8f961a607
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

set(workshop_SOURCES
    "include/framework.h"
    "include/utils.h"
    "src/framework.c"
    "src/utils.c"
)

add_library(workshop_framework ${workshop_SOURCES})
target_include_directories(workshop_framework PUBLIC include)
target_link_libraries(workshop_framework glfw glad)
