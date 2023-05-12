#include <iostream>
#include <fstream>
#include "lexer.hpp"
#include "token.hpp"

using namespace std;


string Lexer::next_token_content() {
    while (ind < code.size() && (code[ind] == ' ' || code[ind] == '\n' || code[ind] == '\t')) {
        line_cnt += (code[ind] == '\n');
        ind++;
    }

    if (ind >= code.size())
        return "";
        
    string ret = "";

    while (code[ind] != ' ' && code[ind] != '\n' && code[ind] != '\t') {
        if (code[ind] == '\'') {
            if (ret != "")
                return ret;
            ind ++;
            return "\'";
        }
            
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
    if(content == "" )
        return Token(content,line_cnt);
    if(content[0] == '\'') {
        Token token("(",line_cnt);
        tokenized_code->push_back(Token("(",line_cnt));
        tokenized_code->push_back(Token("quote",line_cnt));
        quote_counter++;
        return next_token();
    }
	return Token(content,line_cnt);
}

void Lexer::scan_code() {
    
    string input;
    while (getline(fin, input)) {
        code+= input + '\n';
    }
    Token token(next_token());
    while (token.content != "") {
        if(token.type == token_type::ERR) {
            error_messages->push_back(token);
        }
        tokenized_code->push_back(token);

        if(quote_counter > 0) {
            if(bracket_counter > 0) {
                if(token.type == token_type::RPAR) {
                    bracket_counter--;
                }
            }

            if(token.type == token_type::LPAR) {
                bracket_counter++;
            }

            while(quote_counter > bracket_counter) {
                tokenized_code->push_back(Token(")",line_cnt));
                quote_counter--;
            }
        }
        token = next_token();
    }
    while(quote_counter > 0) {
        tokenized_code->push_back(Token(")",line_cnt));
        quote_counter--;
    }
    if(error_messages->size() != 0)
        tokenized_code->clear();
}

void Lexer::print(string filename) {
    if(error_messages && error_messages->size() != 0)
        return;
    filebuf file;
    file.open(filename, ios::out);
    ostream fout(&file);
    for (auto token: *tokenized_code) {
        fout<<token<<endl;
    }
    file.close();
}

void Lexer::print() {
    if(error_messages && error_messages->size() != 0)
        return;
    for (auto token: *tokenized_code) {
        cout<<token<<endl;
    }
}

void Lexer::print_errors() {
    if(error_messages && error_messages->size() == 0)
        return;
    cout<<"Lexical error(s):\n";
    for(auto err:*error_messages) {
        cout<<err;
    }
}

vector < Token > *Lexer::get_tokens() {
    if(tokenized_code->size() != 0 && error_messages->size() != 0)
        return tokenized_code;
    if(error_messages->size() != 0)
        return NULL;
    scan_code();
    if(error_messages->size() != 0)
        return NULL;
    return tokenized_code;
    
}