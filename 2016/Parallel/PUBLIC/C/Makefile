OPTIONS= -pthread -Wall
SHELL=/bin/bash

all : GOL

GOL : GoL.o
	mkdir -p bin
	@gcc ${OPTIONS} GoL.o -o bin/GOL

GoL.o : GoL.c
	@gcc ${OPTIONS} -c -o GoL.o GoL.c

clean:
	@rm -rf bin/GOL bin *~ *.o outputMatrix/*.txt testsMatrix/*.txt

