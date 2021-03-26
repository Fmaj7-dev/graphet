emcc -I./src/render/ -I./src/ui src/app/main.cpp -c -o build/main.o
emcc -I./src/render/ src/render/particlesystem.cpp -c -o build/particlesystem.o
emcc -I./src/render/ src/render/segmentsystem.cpp -c -o build/segmentsystem.o
emcc -I./src/render/ src/render/rendermanager.cpp -c -o build/rendermanager.o
emcc -I./src/ui/ -I./src/render src/ui/windowmanager.cpp -c -o build/windowmanager.o
emcc build/main.o build/segmentsystem.o build/particlesystem.o build/rendermanager.o build/windowmanager.o -o build/app.html
