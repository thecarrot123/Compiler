VPATH= ./include:./src:./build:
CFLAGS = -std=c++17 -I include/

compiler: build/token.o build/lexer.o build/syntaxer.o build/syntax_nodes.o build/semantic_nodes.o build/semantixer.o node.hpp compiler.cpp
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
	./run_tests.sh

clear:
	rm -f *.o
	rm -f compiler
	rm -f build/*