# tell cmake to include this
#include_directories(${CMAKE_CURRENT_SOURCE_DIR))

# source files
set (LIBGRAPH_SOURCES
graph.cpp
)

# we are making a library
add_library(graph ${LIBGRAPH_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)


target_compile_options(graph PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions)
