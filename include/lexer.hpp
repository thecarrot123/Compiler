#ifndef LEXER_HEADER
#define LEXER_HEADER
#include <iostream>
#include <fstream>
#include <vector>
#include "token.hpp"

using namespace std;

class Lexer {
private:
    vector < Token > *tokenized_code;
    vector < string > *error_messages; 
    istream &fin;
    string code = "";
    int ind = 0;
    int quote_counter = 0;
    int bracket_counter = 0;
    int line_cnt = 1;

    string next_token_content();
    Token next_token();
    void scan_code();

public:
    Lexer(ifstream &in) : fin(in){
        tokenized_code = new vector < Token >;
        error_messages = new vector < string >;
    }
    Lexer(istream &in) : fin(in) {
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