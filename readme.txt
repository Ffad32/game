

set working directory
cd c:\home\user\main

64-bit version

compile:
gcc -fdiagnostics-color=always -g main.c -o bin/x64/main.exe -I include -L lib/x64 -lSDL2 -lSDL2_image

start
.\bin\x64\main.exe


32-bit version\

compile:
gcc -fdiagnostics-color=always -g main.c -o bin/x32/main.exe -I include -L lib/x32 -lSDL2 -lSDL2_image

start
.\bin\x32\main.exe









gcc -dumpmashine