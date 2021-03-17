#triangle: triangle.cpp
#	emcc triangle.cpp -o $(OUTPUT)/triangle.html

#mac: main.cpp
#	clang++ -std=c++11 main.cpp -framework GLUT -framework OpenGl -o $(OUTPUT)/graph

#em: main.cpp
#	#emcc graph.cpp -s LEGACY_GL_EMULATION=1 -o $(OUTPUT)/graph.html
#	emcc main.cpp -o $(OUTPUT)/graph.html

all:
	make -C libgraphs
	make -C librender
	make -C app

clean:
	make clean -C app
	make clean -C libgraphs
	make clean -C librender

