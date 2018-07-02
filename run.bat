gcc src/*.c -I./include/ -I./dependencies/SDL2/include/ -L./dependencies/SDL2/lib/ -lmingw32 -lSDL2main -lSDL2 -o bin/pong.exe && cd bin && pong.exe
pause