# minimum version
cmake_minimum_required(VERSION 2.8)

# project name
project( graphet )

# tell cmake to include the current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_CXX_COMPILER emcc)
set(CMAKE_CXX_LINK_EXECUTABLE emcc)
SET(CMAKE_LINKER emcc)


# output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/render)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/graph)

# tell cmake to search for more CMakeLists.txt files in these folders
add_subdirectory(src/render)
add_subdirectory(src/graph)

# main executable
add_executable(graphet src/app/main.cpp)

# tell cmake to include these libraries in the linking
target_link_libraries(graphet graph render "-framework GLUT -framework OpenGl")

#link_directories(/usr/local/mysql/lib)

if(MSVC)
  target_compile_options(graphet PRIVATE /W4 /WX)
else()
  target_compile_options(graphet PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions)
endif()

install(TARGETS graphet DESTINATION bin)
