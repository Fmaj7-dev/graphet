add_executable( check 
                testParticles.cpp
                testGraph.cpp
                testSymmetricMatrix.cpp )

target_link_libraries(check render graph ui math "-framework GLUT -framework OpenGl")
install(TARGETS check DESTINATION build)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)


target_compile_options(check PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions)
