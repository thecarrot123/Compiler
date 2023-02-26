#include <iostream>
#include <fstream>
#include "lexer.hpp"
#include "syntaxer.hpp"

using namespace std;

vector < Token > *tokenized_code;

int main(int argc, char *argv[]){
    if (argc != 2) {
        cout<<"Usage: ./compiler <program.F>\n";
        return 0;
    }
    string file_name = argv[1];
    ifstream file(file_name);
    if(!file.good()) {
        cout<<"Error: file "<<argv[1]<<" doesn't exists\n";
        exit(1);
    }
    Lexer lexer(file_name);
    tokenized_code = lexer.scan_code();
    for(auto x: *tokenized_code) {
        cout<<x<<endl;
    }
    Syntaxer syntaxer(tokenized_code);
    
    return 0;
}