#ifndef PREDEFINED_FUNCTIONS_HEADER
#define PREDEFINED_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"

enum PredefinedFunTypes {
    _plus,
    _minus,
    _times,
    _divide,
    _equal,
    _nonequal,
    _less,
    _lesseq,
    _greater,
    _greatereq,
    _and,
    _or,
    _xor,
    _not,
    _isint,
    _isreal,
    _isbool,
    _isnull,
    _isatom,
    _islist,
    _head,
    _tail,
    _cons,
    _isempty
};

class PredefinedFun {
protected: 
    PredefinedFunTypes name;
    NodeList *params;
    vector <Token> &tokenized_code;
    void print_error(string message, int code) {
        cout<<"Error: "<<message<<endl;
        exit(code);
    }

public:
    PredefinedFun(PredefinedFunTypes name, NodeList *params, vector <Token> &vec) : tokenized_code(vec){
        this->name = name;
        this->params = params;
        //check();
    }
    virtual void typecheck() = 0;
    virtual Node* run() = 0;
};

#endif