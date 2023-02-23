#include <iostream>
#include <fstream>
#include "lexer.hpp"

using namespace std;

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
    cout<<lexer.scan_code()<<endl;

    return 0;
}