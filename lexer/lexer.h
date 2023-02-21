#ifndef LEXER_HEADER
#define LEXER_HEADER
#include <fstream>
#include "token.h"

using namespace std;

class Lexer {
private:
    const int keywords_number = 9;
    ifstream fin;
    string code = "";
    int ind=0;
    string keywords[9] = {"quote", "setq", "func", "lambda", "prog", "cond", "while", "return", "break"};

    bool is_null(const string &s);
    bool is_bracket(char c);
    bool is_boolean(const string &s);
    bool is_integer(const string &s);
    bool is_real(const string &s);
    bool is_literal(const string &s);
    bool is_keyword(const string &s);
    bool is_atom(const string &s);
    string token_type(const string &s);
    string next_token_content();
    Token next_token();

public:
    Lexer (string filename) {
        fin.open(filename);
    }
    string scan_code();
};
#endif