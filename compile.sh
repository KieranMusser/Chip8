[ ! -d bin ] && mkdir bin
cc -Wall -lncurses src/render.c src/chip8.c src/main.c -o bin/chip8
