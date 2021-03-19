# tell cmake to include this
#include_directories(${CMAKE_CURRENT_SOURCE_DIR)/include)

# source files
set (LIBRENDER_SOURCES
particlesystem.cpp
)

# we are making a library
add_library(render ${LIBRENDER_SOURCES})

