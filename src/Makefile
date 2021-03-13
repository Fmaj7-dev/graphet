OUTPUT=../build

triangle: triangle.cpp
	emcc triangle.cpp -o $(OUTPUT)/triangle.html

mac: graph.cpp
	#-s LEGACY_GL_EMULATION=1
	#emcc graph.cpp  -o $(OUTPUT)/graph.html
	clang++ -std=c++11 graph.cpp -framework GLUT -framework OpenGl -o $(OUTPUT)/graph

em: graph.cpp
	emcc graph.cpp  -o $(OUTPUT)/graph.html