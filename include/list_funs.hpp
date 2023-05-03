#ifndef LIST_FUNCTIONS_HEADER
#define LIST_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class ListFun : public PredefinedFun {
protected:
    void typecheck() override;

public:
    ListFun(PredefinedFunTypes name, NodeList *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}

    void strip(int idx);

    int p1_size();
};

class HeadFun : public ListFun {
public:
    void typecheck() override;

    HeadFun(NodeList *params, vector <Token> &vec) : ListFun(_head,params,vec) {
        strip(1);
    }

    Node* run() override;

};

class TailFun : public ListFun {
public:
    void typecheck() override;

    TailFun(NodeList *params, vector <Token> &vec) : ListFun(_tail,params,vec) {
        strip(1);
    }

    Node* run() override;

};

class ConsFun : public ListFun {
public:
    void typecheck() override;

    ConsFun(NodeList *params, vector <Token> &vec) : ListFun(_cons,params,vec) {
        strip(2);
    }

    Node* run() override;

};

class IsEmptyFun : public ListFun {
public:
    void typecheck() override;

    IsEmptyFun(NodeList *params, vector <Token> &vec) : ListFun(_isempty,params,vec) {
        strip(1);
    }

    Node* run() override;
};

#endif