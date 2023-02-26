#include <iostream>
#include "lexer.hpp"
#include "token.hpp"

using namespace std;
int line_cnt = 1;

string Lexer::next_token_content() {
    while (ind < code.size() && (code[ind] == ' ' || code[ind] == '\n' || code[ind] == '\t')) {
        line_cnt += (code[ind] == '\n');
        ind++;
    }

    if (ind >= code.size())
        return "";
        
    string ret = "";

    while (code[ind] != ' ' && code[ind] != '\n' && code[ind] != '\t') {
        if (code[ind] == '(' || code[ind] == ')') {
            if (ret != "")
                return ret;
            ret = code[ind];
            ind ++;
            return ret;
        }
        if(code[ind] == '/' && code[ind+1] == '/') {
            while (code[ind] != '\n' && code[ind] != EOF) 
                ind++;
            if (ret == "")
                return next_token_content();
            break;
        }
        ret += code[ind];
        ind++;
    }
    return ret;
}

Token Lexer::next_token() {
    string content = next_token_content();
	return Token(content,line_cnt);
}

vector < Token > *Lexer::scan_code() {
    string input;
    while (getline(fin, input)) {
        code+= input + '\n';
    }
    vector < Token > *tokenized_code = new vector < Token >;
    Token token(next_token());
    while (token.content != "") {
        tokenized_code->push_back(token);
        token = next_token();
    }
    return tokenized_code;
}