add_executable( check 
                testParticles.cpp )

target_link_libraries(check render)
install(TARGETS check DESTINATION build)

target_compile_options(check PRIVATE -Wall -Wextra -pedantic -Werror -std=c++17 -Wc++11-extensions)
