[ ! -d bin ] && mkdir bin
cc -DNO_CURS -Wall src/chip8.c src/main.c -o bin/chip8
