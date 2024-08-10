build:
	gcc -std=c99 -Wall ./lib/lua/src/*.c ./src/*.c -o main

run:
	./main

clean:
	rm main