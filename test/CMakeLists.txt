add_executable( check 
                testParticles.cpp
                testGraph.cpp )

target_link_libraries(check render graph "-framework GLUT -framework OpenGl")
install(TARGETS check DESTINATION build)

target_compile_options(check PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions)
