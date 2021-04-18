# tell cmake to include this
#include_directories(${CMAKE_CURRENT_SOURCE_DIR))

# source files
set (LIBMATH_SOURCES
symmetric_matrix.cpp
)

# we are making a library
add_library(math ${LIBMATH_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../external/glm/)


target_compile_options(math PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions)
