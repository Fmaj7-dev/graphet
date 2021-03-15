OUTPUT=../build

triangle: triangle.cpp
	emcc triangle.cpp -o $(OUTPUT)/triangle.html

mac: graph.cpp
	clang++ -std=c++11 graph.cpp -framework GLUT -framework OpenGl -o $(OUTPUT)/graph

em: graph.cpp
	#emcc graph.cpp -s LEGACY_GL_EMULATION=1 -o $(OUTPUT)/graph.html
	emcc graph.cpp -o $(OUTPUT)/graph.html