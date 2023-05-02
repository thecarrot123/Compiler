#ifndef LOGIC_FUNCTIONS_HEADER
#define LOGIC_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class LogicalFun : public PredefinedFun {
protected:
    NodeParams *create_params();

    void typecheck() override;
    
    bool get_logical_val(NodeTerminal *node);

public:

    LogicalFun(PredefinedFunTypes name, NodeParams *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}
};

class AndFun : public LogicalFun {
public:
    AndFun(vector <Token> &vec) : LogicalFun(_and,create_params(),vec) {}

    AndFun(NodeParams *params, vector <Token> &vec) : LogicalFun(_and,params,vec) { }

    Node* run() override;

};

class OrFun : public LogicalFun {
public:
    OrFun(vector <Token> &vec) : LogicalFun(_or,create_params(),vec) {}

    OrFun(NodeParams *params, vector <Token> &vec) : LogicalFun(_or,params,vec) { }

    Node* run() override;

};

class XorFun : public LogicalFun {
public:
    XorFun(vector <Token> &vec) : LogicalFun(_xor,create_params(),vec) {}

    XorFun(NodeParams *params, vector <Token> &vec) : LogicalFun(_xor,params,vec) { }

    Node* run() override;

};

class NotFun : public LogicalFun {
public:
    NodeParams *create_params();

    void typecheck() override;

    NotFun(vector <Token> &vec) : LogicalFun(_not,create_params(),vec) {}

    NotFun(NodeParams *params, vector <Token> &vec) : LogicalFun(_not,params,vec) { }

    Node* run() override;
};

#endif