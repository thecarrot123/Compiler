#ifndef LEXER_HEADER
#define LEXER_HEADER
#include <fstream>
#include <vector>
#include "token.hpp"

using namespace std;

class Lexer {
private:
    vector < Token > *tokenized_code;
    vector < string > *error_messages; 
    ifstream fin;
    string code = "";
    int ind=0;

    string next_token_content();
    Token next_token();
    void scan_code();

public:
    Lexer(string filename) {
        fin.open(filename);
        tokenized_code = new vector < Token >;
        error_messages = new vector < string >;
    }
    ~Lexer() {
        delete tokenized_code;
        delete error_messages;
    }
    void print();
    void print_errors();
    void print(string filename);
    vector < Token > *get_tokens();
};
#endif