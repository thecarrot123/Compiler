all:
	g++ lexer/lexer.cpp lexer/lexer.h compiler.cpp -o compiler
run_tests:
	g++ lexer/lexer.cpp lexer/lexer.h compiler.cpp -o compiler
	./compiler tests/in/1.F > tests/lexer_output/1.lex
	./compiler tests/in/2.F > tests/lexer_output/2.lex
	./compiler tests/in/3.F > tests/lexer_output/3.lex
clear:
	rm -f compiler
	rm tests/lexer_output/*