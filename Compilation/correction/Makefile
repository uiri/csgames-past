all: interpret
	./tests.sh programs/*.m

interpret:
	test -d bin || mkdir bin; cd src; make

clean:
	cd src; make clean; cd ..; rm out/*
