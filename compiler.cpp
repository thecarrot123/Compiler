#include <getopt.h>
#include <iostream>
#include <fstream>
#include <map>
#include "lexer.hpp"
#include "syntaxer.hpp"

using namespace std;

vector < Token > *tokenized_code;

class ArgReader {
private:
    int argc;
    char **argv;

    map < char , string > parsed_args;
    const char required[1] = {'f'};

    void readArgs() {

        int opt;

        while (true) {
            opt = getopt(argc, argv, "l:s:f:h");
            switch(opt) {
                case 'f':
                    parsed_args['f'] = optarg;
                    continue;

                case 'l':
                    parsed_args['l'] = optarg;
                    continue;
                case 's':
                    parsed_args['s'] = optarg;
                    continue;
                case 'h':
                    printHelp();
                    exit(0);
                case -1:
                    for(auto c:required) {
                        if (parsed_args[c] == "") {
                            printHelp();
                            exit(0);
                        }
                    }
                    break;
            }

            break;
        }
    }

public:
    ArgReader(int argc, char **argv) {
        this->argc = argc;
        this->argv = argv;
        readArgs();
    }

    string getArg(char arg) {
        return parsed_args[arg];
    }

    void printHelp() {
        printf("Usage: ./compiler -f <program.dl> [Options] \n");
        printf("Options: \n\
        \t-f <program.dl>:\tSource code to be compiled. This is a required argument\n\
        \t[-l <output>]:\tPrint the output of lexer to <output> file.\n\
        \t[-s <output>]:\tPrint the output of syntax analyzer to <output> file.\n");
    }
};


int main(int argc, char **argv) {
    
    ArgReader args(argc, argv);

    string file_name = args.getArg('f');
    ifstream file(file_name);
    if(!file.good()) {
        cout<<"Error: file "<<file_name<<" doesn't exists\n";
        exit(1);
    }
    Lexer lexer(file_name);
    tokenized_code = lexer.scan_code();
    if (args.getArg('l') != "") {
        lexer.print(args.getArg('l'));
    }
    Syntaxer syntaxer(tokenized_code);
    if (args.getArg('s') != "") {
        
    }
    file.close();
    return 0;
}