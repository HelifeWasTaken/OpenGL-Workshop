cmake_minimum_required(VERSION 3.11)

project(workshop_opengl)

add_subdirectory(framework)
add_subdirectory(src)

# Place the executable at the root of the repository
set_target_properties(main
    PROPERTIES
        RUNTIME_OUTPUT_NAME "main"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}
)
