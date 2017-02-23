OPTIONS= -ltbb -std=c++11 -O2 -Wall
SHELL=/bin/bash

all : GOL

GOL : GoL.o
	mkdir -p bin
	@g++ ${OPTIONS} GoL.o -o bin/GOL

GoL.o : GoL.cpp
	@g++ ${OPTIONS} -c -o GoL.o GoL.cpp

clean:
	@rm -rf bin/GOL bin *~ *.o outputMatrix/*.txt testsMatrix/*.txt
