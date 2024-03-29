#include <getopt.h>
#include <iostream>
#include <fstream>
#include <map>
#include "lexer.hpp"
#include "syntaxer.hpp"
#include "semantixer.hpp"
#include "interpreter.hpp"

using namespace std;

class ArgReader {
private:
    int argc;
    char **argv;

    map < char , string > parsed_args;
    const char required[1] = {'f'};

    void readArgs() {

        int opt;

        while (true) {
            opt = getopt(argc, argv, "l:s:S:f:h");
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
                case 'S':
                    parsed_args['S'] = optarg;
                    continue;
                case 'h':
                    printHelp();
                    exit(1);
                case -1:
                    for(auto c:required) {
                        if (parsed_args[c] == "") {
                            printHelp();
                            exit(1);
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
        \t[-s <output>]:\tPrint the output of syntax analyzer to <output> file.\n\
        \t[-S <output>]:\tPrint the output of semantic analyzer to <output> file.\n");
    }
};

vector < Token > *tokenized_code;

int main(int argc, char **argv) {
    
    ArgReader args(argc, argv);

    string file_name = args.getArg('f');
    ifstream file(file_name);
    if(!file.good()) {
        cout<<"Error: file "<<file_name<<" doesn't exists\n";
        exit(1);
    }
    Lexer lexer(file);
    tokenized_code = lexer.get_tokens();
    if (tokenized_code == NULL) {
        lexer.print_errors();
        exit(2);
    }
    if (args.getArg('l') != "") {
        lexer.print(args.getArg('l'));
    }
    Syntaxer syntaxer(tokenized_code);
    Node* root = syntaxer.get_root();
    if (root == NULL) {
        syntaxer.print_errors();
        exit(3);
    }
    if (args.getArg('s') != "") {
        syntaxer.print(args.getArg('s'), root);
    }
    Semantixer semantixer(root);
    root = semantixer.traverse();
    if (root == NULL) {
        semantixer.print_errors();
        exit(4);
    }
    if (args.getArg('S') != "") {
        semantixer.print(args.getArg('S'));
    }
    int prog_params = semantixer.prog_params;
    Node* param_root = NULL;
    if(prog_params) {
        cout<<"Enter prog params:\n";
        Lexer param_lexer(cin);
        vector < Token > * param_token = param_lexer.get_tokens();
        if (param_token == NULL) {
            param_lexer.print_errors();
            exit(2);
        }
        for(auto token: *param_token) {
            if(token.type == ATOM || (token.type == KEYWORD && token.content != "quote")) {
                cout<<"Error: Params can't have atoms or keywords\n";
                exit(2);
            }
        }
        Syntaxer param_syntaxer(param_token);
        param_root = param_syntaxer.get_root();
        if (param_root == NULL) {
            param_syntaxer.print_errors();
            exit(3);
        }
        Semantixer param_semantixer(param_root,false);
        param_root = param_semantixer.traverse();
        if (param_root == NULL) {
            param_semantixer.print_errors();
            exit(4);
        }
        param_semantixer.print("sample.sem");
        if((int)param_root->children.size() != prog_params) {
            cout<<"Error: Prog has "<<prog_params<<" params but got "<<(int)param_root->children.size()<<endl;
            exit(4);
        }
    }
    Interpreter interpreter(root,param_root);
    interpreter.interpret();
    file.close();
    return 0;
}