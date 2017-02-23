all: interpret tests
	
interpret: grammar
	mkdir -p bin
	javac src/java/Interpret.java -classpath src/java -d bin
	
grammar:
	java -jar sablecc-4-beta.2/lib/sablecc.jar src/java/squelette.sablecc -d src/java/

tests:
	./tests.sh programs/*.m

clean:
	rm -rf bin
	rm -rf src/java/language_mpire
