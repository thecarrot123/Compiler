VPATH= ./include:./src:./build:
CFLAGS = -std=c++17 -I include/

compiler: build/token.o build/lexer.o build/syntaxer.o build/syntax_nodes.o build/semantic_nodes.o build/semantixer.o compiler.cpp
	g++ $(CFLAGS) $^ -o $@

build/lexer.o: lexer.cpp lexer.hpp
	g++ $(CFLAGS) -c $< -o $@

build/token.o: token.cpp token.hpp
	g++ $(CFLAGS) -c $< -o $@

build/syntaxer.o: syntaxer.cpp syntaxer.hpp 
	g++ $(CFLAGS) -c $< -o $@

build/syntax_nodes.o: syntax_nodes.cpp syntax_nodes.hpp
	g++ $(CFLAGS) -c $< -o $@

build/semantixer.o: semantixer.cpp semantixer.hpp 
	g++ $(CFLAGS) -c $< -o $@

build/semantic_nodes.o: semantic_nodes.cpp semantic_nodes.hpp
	g++ $(CFLAGS) -c $< -o $@

run_tests: compiler
	./compiler -f tests/in/1.dl -l tests/lexer_output/1.lex -s tests/syntaxer_output/1.syn
	./compiler -f tests/in/2.dl -l tests/lexer_output/2.lex -s tests/syntaxer_output/2.syn
	./compiler -f tests/in/3.dl -l tests/lexer_output/3.lex -s tests/syntaxer_output/3.syn
	./compiler -f tests/in/4.dl -l tests/lexer_output/4.lex -s tests/syntaxer_output/4.syn
	dot -Tpng tests/syntaxer_output/1.syn > tests/syntaxer_visualization/1.png
	dot -Tpng tests/syntaxer_output/3.syn > tests/syntaxer_visualization/3.png

clear:
	rm -f *.o
	rm -f compiler
	rm -f build/*