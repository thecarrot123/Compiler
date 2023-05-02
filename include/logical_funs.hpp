#ifndef LOGIC_FUNCTIONS_HEADER
#define LOGIC_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class LogicalFun : public PredefinedFun {
protected:
    void typecheck() override;
    
    bool get_logical_val(NodeTerminal *node);

public:

    LogicalFun(PredefinedFunTypes name, NodeList *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}
};

class AndFun : public LogicalFun {
public:
    AndFun(NodeList *params, vector <Token> &vec) : LogicalFun(_and,params,vec) { }

    Node* run() override;

};

class OrFun : public LogicalFun {
public:
    OrFun(NodeList *params, vector <Token> &vec) : LogicalFun(_or,params,vec) { }

    Node* run() override;

};

class XorFun : public LogicalFun {
public:
    XorFun(NodeList *params, vector <Token> &vec) : LogicalFun(_xor,params,vec) { }

    Node* run() override;

};

class NotFun : public LogicalFun {
public:
    void typecheck() override;

    NotFun(NodeList *params, vector <Token> &vec) : LogicalFun(_not,params,vec) { }

    Node* run() override;
};

#endif