VPATH= ./include:./src:./build:
CFLAGS = -std=c++17 -I include/

compiler: build/token.o build/lexer.o build/syntaxer.o compiler.cpp
	g++ $(CFLAGS) $^ -o $@

build/lexer.o: lexer.cpp lexer.hpp
	g++ $(CFLAGS) -c $< -o $@

build/token.o: token.cpp token.hpp
	g++ $(CFLAGS) -c $< -o $@

build/syntaxer.o: syntaxer.cpp syntaxer.hpp
	g++ $(CFLAGS) -c $< -o $@

build/syntaxer_node.o: syntaxer_node.cpp syntaxer_node.hpp
	g++ $(CFLAGS) -c $< -o $@

run_tests: compiler
	./compiler -f tests/in/1.dl -l tests/lexer_output/1.lex 
	./compiler -f tests/in/2.dl -l tests/lexer_output/2.lex 
	./compiler -f tests/in/3.dl -l tests/lexer_output/3.lex 

clear:
	rm -f *.o
	rm -f compiler
	rm -f build/*