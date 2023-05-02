#ifndef PREDICATE_FUNCTIONS_HEADER
#define PREDICATE_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class PredicateFun : public PredefinedFun {
protected: 
    void typecheck() override;
    
    NodeType get_predicate_val(Node *node);

public:

    PredicateFun(PredefinedFunTypes name, NodeList *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}

};

class IsIntFun : public PredicateFun {
public:
    IsIntFun(NodeList *params, vector <Token> &vec) : PredicateFun(_isint,params,vec) { }

    Node* run() override;
};

class IsRealFun : public PredicateFun {
public:
    IsRealFun(NodeList *params, vector <Token> &vec) : PredicateFun(_isreal,params,vec) { }

    Node* run() override;
};

class IsBoolFun : public PredicateFun {
public:
    IsBoolFun(NodeList *params, vector <Token> &vec) : PredicateFun(_isbool,params,vec) { }

    Node* run() override;
};

class IsNullFun : public PredicateFun {
public:
    IsNullFun(NodeList *params, vector <Token> &vec) : PredicateFun(_isnull,params,vec) { }

    Node* run() override;
};

class IsAtomFun : public PredicateFun {
public:
    IsAtomFun(NodeList *params, vector <Token> &vec) : PredicateFun(_isatom,params,vec) { }

    Node* run() override;
};

class IsListFun : public PredicateFun {
public:
    IsListFun(NodeList *params, vector <Token> &vec) : PredicateFun(_islist,params,vec) { }

    Node* run() override;
};

#endif