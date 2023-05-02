#ifndef LIST_FUNCTIONS_HEADER
#define LIST_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class ListFun : public PredefinedFun {
protected:
    NodeParams *create_params();

    void typecheck() override;


public:

    ListFun(PredefinedFunTypes name, NodeParams *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}

    int p1_size();
};

class HeadFun : public ListFun {
public:
    void typecheck() override;

    HeadFun(vector <Token> &vec) : ListFun(_head,create_params(),vec) {}

    HeadFun(NodeParams *params, vector <Token> &vec) : ListFun(_head,params,vec) { }

    Node* run() override;

};

class TailFun : public ListFun {
public:
    void typecheck() override;

    TailFun(vector <Token> &vec) : ListFun(_tail,create_params(),vec) {}

    TailFun(NodeParams *params, vector <Token> &vec) : ListFun(_tail,params,vec) { }

    Node* run() override;

};

class ConsFun : public ListFun {
public:
    NodeParams *create_params();

    void typecheck() override;

    ConsFun(vector <Token> &vec) : ListFun(_cons,create_params(),vec) {}

    ConsFun(NodeParams *params, vector <Token> &vec) : ListFun(_cons,params,vec) { }

    Node* run() override;

};

class IsEmptyFun : public ListFun {
public:
    IsEmptyFun(vector <Token> &vec) : ListFun(_isempty,create_params(),vec) {}

    IsEmptyFun(NodeParams *params, vector <Token> &vec) : ListFun(_isempty,params,vec) { }

    Node* run() override;
};

#endif