all: gol_seq gol_para
	mkdir -p bin
	gcc src/gol.o -o bin/gol
	gcc -pthread src/gol_para.o -o bin/gol_para

gol_seq:
	gcc -g -O2 -c src/gol.c -o src/gol.o

gol_para:
	gcc -pthread -g -O2 -c src/gol_para.c -o src/gol_para.o

clean:
	rm bin/*
	rm src/*.o
