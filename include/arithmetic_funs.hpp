#ifndef ARITHMETIC_FUNCTIONS_HEADER
#define ARITHMETIC_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class ArithmeticFun : public PredefinedFun {
protected:
    NodeParams *create_params();

    void typecheck() override;
    
    double get_arithmetic_val(NodeTerminal *node);

public:

    ArithmeticFun(PredefinedFunTypes name, NodeParams *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}
};

class PlusFun : public ArithmeticFun {
public:
    PlusFun(vector <Token> &vec) : ArithmeticFun(_plus,create_params(),vec) {}

    PlusFun(NodeParams *params, vector <Token> &vec) : ArithmeticFun(_plus,params,vec) {}

    Node* run() override;
};

class MinusFun : public ArithmeticFun {
public:
    MinusFun(vector <Token> &vec) : ArithmeticFun(_minus,create_params(),vec) {}

    MinusFun(NodeParams *params, vector <Token> &vec) : ArithmeticFun(_minus,params,vec) {}

    Node* run() override;
};

class TimesFun : public ArithmeticFun {
public:
    TimesFun(vector <Token> &vec) : ArithmeticFun(_times,create_params(),vec) {}

    TimesFun(NodeParams *params, vector <Token> &vec) : ArithmeticFun(_times,params,vec) {}

    Node* run() override;
};

class DivideFun : public ArithmeticFun {
private:

    void typecheck() override;

public:
    DivideFun(vector <Token> &vec) : ArithmeticFun(_divide,create_params(),vec) {}

    DivideFun(NodeParams *params, vector <Token> &vec) : ArithmeticFun(_divide,params,vec) { }

    Node* run() override;

};

#endif


