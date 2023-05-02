#ifndef PREDICATE_FUNCTIONS_HEADER
#define PREDICATE_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class PredicateFun : public PredefinedFun {
protected: 
    NodeParams *create_params();

    void typecheck() override;
    
    NodeType get_predicate_val(Node *node);

public:

    PredicateFun(PredefinedFunTypes name, NodeParams *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}

};

class IsIntFun : public PredicateFun {
public:
    IsIntFun(vector <Token> &vec) : PredicateFun(_isint,create_params(),vec) {}

    IsIntFun(NodeParams *params, vector <Token> &vec) : PredicateFun(_isint,params,vec) { }

    Node* run() override;
};

class IsRealFun : public PredicateFun {
public:
    IsRealFun(vector <Token> &vec) : PredicateFun(_isreal,create_params(),vec) {}

    IsRealFun(NodeParams *params, vector <Token> &vec) : PredicateFun(_isreal,params,vec) { }

    Node* run() override;
};

class IsBoolFun : public PredicateFun {
public:
    IsBoolFun(vector <Token> &vec) : PredicateFun(_isbool,create_params(),vec) {}

    IsBoolFun(NodeParams *params, vector <Token> &vec) : PredicateFun(_isbool,params,vec) { }

    Node* run() override;
};

class IsNullFun : public PredicateFun {
public:
    IsNullFun(vector <Token> &vec) : PredicateFun(_isnull,create_params(),vec) {}

    IsNullFun(NodeParams *params, vector <Token> &vec) : PredicateFun(_isnull,params,vec) { }

    Node* run() override;
};

class IsAtomFun : public PredicateFun {
public:
    IsAtomFun(vector <Token> &vec) : PredicateFun(_isatom,create_params(),vec) {}

    IsAtomFun(NodeParams *params, vector <Token> &vec) : PredicateFun(_isatom,params,vec) { }

    Node* run() override;
};

class IsListFun : public PredicateFun {
public:
    IsListFun(vector <Token> &vec) : PredicateFun(_islist,create_params(),vec) {}

    IsListFun(NodeParams *params, vector <Token> &vec) : PredicateFun(_islist,params,vec) { }

    Node* run() override;
};

#endif