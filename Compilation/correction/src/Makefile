all: minilang

minilang: minilang.nit minilang_parser.nit
	nitc minilang.nit -o ../bin/minilang

minilang_parser.nit: minilang.sablecc
	nitcc minilang.sablecc

clean:
	rm *.out; rm *.dot; rm minilang_lexer.nit; rm minilang_parser.nit; rm minilang_test_parser.nit;
