build:
	gcc -std=c99 -Wall ./lib/lua/src/*.c ./src/*.c `sdl2-config --cflags` `sdl2-config --libs` -o main

run:
	./main

clean:
	rm main