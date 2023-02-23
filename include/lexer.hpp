#ifndef LEXER_HEADER
#define LEXER_HEADER
#include <fstream>
#include "token.hpp"

using namespace std;

class Lexer {
private:
    ifstream fin;
    string code = "";
    int ind=0;

    string next_token_content();
    Token next_token();

public:
    Lexer (string filename) {
        fin.open(filename);
    }
    string scan_code();
};
#endif