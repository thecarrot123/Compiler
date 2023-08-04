#ifndef ARITHMETIC_FUNCTIONS_HEADER
#define ARITHMETIC_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class ArithmeticFun : public PredefinedFun {
protected:
    void typecheck() override;
    
    double get_arithmetic_val(NodeTerminal *node);

public:

    ArithmeticFun(PredefinedFunTypes name, NodeList *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}
};

class PlusFun : public ArithmeticFun {
public:
    PlusFun(NodeList *params, vector <Token> &vec) : ArithmeticFun(_plus,params,vec) {}

    Node* run() override;
};

class MinusFun : public ArithmeticFun {
public:
    MinusFun(NodeList *params, vector <Token> &vec) : ArithmeticFun(_minus,params,vec) {}

    Node* run() override;
};

class TimesFun : public ArithmeticFun {
public:
    TimesFun(NodeList *params, vector <Token> &vec) : ArithmeticFun(_times,params,vec) {}

    Node* run() override;
};

class DivideFun : public ArithmeticFun {
private:

    void typecheck() override;

public:
    DivideFun(NodeList *params, vector <Token> &vec) : ArithmeticFun(_divide,params,vec) { }

    Node* run() override;

};

class ModFun : public ArithmeticFun {
private:

    void typecheck() override;

public:
    ModFun(NodeList *params, vector <Token> &vec) : ArithmeticFun(_mod,params,vec) {}

    Node* run() override;
};

#endif


