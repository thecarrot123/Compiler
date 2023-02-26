#include "syntaxer.hpp"
#include "token.hpp"
#include <stack>
#include <stdio.h>

using namespace std;

stack < int > parentheses;

bool Syntaxer::check_brackets(){
    for(int i=0;i<size();i++) {
        if(tokenized_code[i].type == token_type::LPAR)
            parentheses.push(i);
        if(tokenized_code[i].type == token_type::RPAR) {
            if(parentheses.size()) {
                int j = parentheses.top();
                bracket_info[j] = i;
                bracket_info[i] = j;
                parentheses.pop();
            }
            else {
                error = 1;
                error_messages.push_back("Error: Unopened parentheses at line " + 
                    to_string(tokenized_code[i].line));
            }
        }
    }
    while(parentheses.size()) {
        error = 1;
        error_messages.push_back("Error: Unclosed parentheses at line " + 
            to_string(tokenized_code[parentheses.top()].line));
        //printf("Error: Unclosed parentheses at line %d\n",tokenized_code[parentheses.top()].line);
        parentheses.pop();
    }
    /*
    for(int i=0;i<size();i++) {
        if(bracket_info[i] != -1) {
            printf("%d: %d\n",i,bracket_info[i]);
        }
    }*/
    return !error;
}

