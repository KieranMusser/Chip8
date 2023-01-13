[ ! -d bin ] && mkdir bin
cc -Wall src/chip8.c src/main.c -o bin/chip8
