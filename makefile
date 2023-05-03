VPATH= ./include:./src:./build:
CFLAGS = -std=c++17 -I include/
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,build/%.o,$(SRCS))

compiler: $(OBJS) predefined_funs.hpp node.hpp compiler.cpp
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

build/arithmetic_funs.o: arithmetic_funs.cpp arithmetic_funs.hpp
	g++ $(CFLAGS) -c $< -o $@

build/comparison_funs.o: comparison_funs.cpp comparison_funs.hpp
	g++ $(CFLAGS) -c $< -o $@

build/logical_funs.o: logical_funs.cpp logical_funs.hpp
	g++ $(CFLAGS) -c $< -o $@

build/predicate_funs.o: predicate_funs.cpp predicate_funs.hpp
	g++ $(CFLAGS) -c $< -o $@

build/list_funs.o: list_funs.cpp list_funs.hpp
	g++ $(CFLAGS) -c $< -o $@

build/interpreter.o: interpreter.cpp interpreter.hpp
	g++ $(CFLAGS) -c $< -o $@

run_tests:
	./run_tests.sh

clear:
	rm -f *.o
	rm -f compiler
	rm -f build/*