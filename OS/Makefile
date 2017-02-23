all: coder decoder simple_coder simple_decoder
	mkdir -p bin
	gcc -g src/filecoder.o src/utils.o -o bin/filecoder
	gcc -g src/filecoder_simple.o src/utils.o -o bin/filecoder_simple
	gcc -g src/filedecoder.o src/utils.o -o bin/filedecoder
	gcc -g src/filedecoder_simple.o src/utils.o -o bin/filedecoder_simple

coder: utils
	gcc -g -c src/filecoder.c -o src/filecoder.o

simple_coder: utils
	gcc -g -c src/filecoder_simple.c -o src/filecoder_simple.o

decoder: utils
	gcc -g -c src/filedecoder.c -o src/filedecoder.o

simple_decoder: utils
	gcc -g -c src/filedecoder_simple.c -o src/filedecoder_simple.o

utils:
	gcc -g -c src/utils.c -o src/utils.o

clean:
	rm bin/*
	rm src/*.o
