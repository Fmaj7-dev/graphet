emcc -I./src/ src/app/main.cpp -c -o build/main.o
emcc -I./src  src/render/particlesystem.cpp -c -o build/particlesystem.o
emcc -I./src  src/render/segmentsystem.cpp -c -o build/segmentsystem.o
emcc -I./src  src/render/rendermanager.cpp -c -o build/rendermanager.o
emcc -I./src  src/ui/windowmanager.cpp -c -o build/windowmanager.o
emcc -I./src  src/graph/graph.cpp -c -o build/graph.o
emcc build/main.o build/segmentsystem.o build/particlesystem.o build/rendermanager.o build/windowmanager.o build/graph.o -o build/app.html
