# tell cmake to include this
#include_directories(${CMAKE_CURRENT_SOURCE_DIR)/include)

# source files
set (LIBUI_SOURCES
windowmanager.cpp
)

# we are making a library
add_library(ui ${LIBUI_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_options(ui PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions )
