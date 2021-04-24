# tell cmake to include this
#include_directories(${CMAKE_CURRENT_SOURCE_DIR)/include)

# source files
set (LIBRENDER_SOURCES
particlesystem.cpp
rendermanager.cpp
segmentsystem.cpp
renderable.cpp
background.cpp
glwrapper.cpp
)

# we are making a library
add_library(render ${LIBRENDER_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../external/glm/)

target_compile_options(render PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions )
