include(CheckLibraryExists)

# Source files - ADD YOUR FILES HERE
set(main_SOURCES
    main.c
)

# Libraries
set(main_LIBRARIES workshop_framework)

# Look for the math library (Windows doesn't need it!)
CHECK_LIBRARY_EXISTS(m sinf "" HAVE_LIB_M)
if(HAVE_LIB_M)
    set(main_LIBRARIES ${main_LIBRARIES} m)
endif()

# Workshop - Main executable
add_executable(main ${main_SOURCES})
target_link_libraries(main ${main_LIBRARIES})
