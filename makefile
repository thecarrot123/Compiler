all:
	g++ lexer/lexer.cpp lexer/lexer.h compiler.cpp -o compiler
run_test:
	g++ lexer/lexer.cpp lexer/lexer.h compiler.cpp -o compiler
	./compiler sample
clear:
	rm -f compiler