CC=gcc
SRC=src
CFLAGS=-std=c99
RELEASE_PATH=challenges

default: all

all: init asm bin1 bin2 bin3 bin4 brainfuck java1 java2 rle tar

init:
	mkdir -p $(RELEASE_PATH)/asm
	mkdir -p $(RELEASE_PATH)/bin1
	mkdir -p $(RELEASE_PATH)/bin2
	mkdir -p $(RELEASE_PATH)/bin3
	mkdir -p $(RELEASE_PATH)/bin4
	mkdir -p $(RELEASE_PATH)/brainfuck
	mkdir -p $(RELEASE_PATH)/java1
	mkdir -p $(RELEASE_PATH)/java2
	mkdir -p $(RELEASE_PATH)/encoding

asm:
	cp $(SRC)/asm/unknown.asm $(RELEASE_PATH)/asm/unkown.asm

bin1:
	$(CC) $(SRC)/bin1/bin1.c -o $(RELEASE_PATH)/bin1/bin1 -lcrypto $(CFLAGS)

bin2:
	$(CC) $(SRC)/bin2/bin2.c -o $(RELEASE_PATH)/bin2/bin2 $(CFLAGS)

bin3:
	$(CC) $(SRC)/bin3/bin3.c -o $(RELEASE_PATH)/bin3/bin3 $(CFLAGS)
	strip $(RELEASE_PATH)/bin3/bin3

bin4:
	$(CC) $(SRC)/bin4/bin4.c -o $(RELEASE_PATH)/bin4/bin4 $(CFLAGS)
	strip $(RELEASE_PATH)/bin4/bin4

brainfuck:
	sed ':a;N;$$!ba;s/\n//g' $(SRC)/brainfuck/prog.bf > $(RELEASE_PATH)/brainfuck/prog.bf

java1:
	cp $(SRC)/java1/src/org/csgames/Java1.java $(RELEASE_PATH)/java1/Java1.java

java2:
	cd $(SRC)/java2/src && javac org/csgames/Java2.java && jar -cvfm ../../../$(RELEASE_PATH)/java2/Java2.jar ../META-INF/MANIFEST.MF org/csgames/*.class

rle:
	cp $(SRC)/rle/rle.c $(RELEASE_PATH)/encoding/encoding.c
	cp $(SRC)/rle/flag.bmp.encoded $(RELEASE_PATH)/encoding/flag.bmp.encoded

tar:
	tar cfv release.tar.gz ./$(RELEASE_PATH)/ ./doc/ ./tools/

clean:
	rm -rf $(RELEASE_PATH)/
