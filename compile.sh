emcc -I./src/render/ src/app/main.cpp -c -o build/main.o
emcc -I./src/render/ src/render/particlesystem.cpp -c -o build/particlesystem.o
emcc build/main.o build/particlesystem.o -o build/app.html
