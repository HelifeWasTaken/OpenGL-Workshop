set(glad_SOURCES
    "include/glad/gl.h"
    "include/KHR/khrplatform.h"
    "src/gl.c"
)

add_library(glad ${glad_SOURCES})
target_include_directories(glad PUBLIC include)
