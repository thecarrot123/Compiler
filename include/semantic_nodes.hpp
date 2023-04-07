#ifndef SEMANTIC_NODES_HEADER
#define SEMANTIC_NODES_HEADER
#include "node.hpp"
#include "syntax_nodes.hpp"
#include <iostream>

class NodeSpecialForm : public NodeList {
public:
    NodeSpecialForm(NodeList* node){
        cout <<"SODFIJSODF\n";
        this->type = SpecialForm;
        this->terminal = false;
        this->tokenized_code = node->get_tokenized_code();
        this->interval = node->get_interval();
        this->bracket_info = node->get_bracket_info();
        this->index = node->get_index();
        this->children = node->children;
    }
    bool typecheck();
};

class QuoteSF : public NodeSpecialForm{
public:
    QuoteSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class SetqSF : public NodeSpecialForm{
public:
    SetqSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class FuncSF : public NodeSpecialForm{
public:
    FuncSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class LambdaSF : public NodeSpecialForm{
public:
    LambdaSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class ProgSF : public NodeSpecialForm{
public:
    ProgSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class CondSF : public NodeSpecialForm{
public:
    CondSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class WhileSF : public NodeSpecialForm{
public:
    WhileSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class ReturnSF : public NodeSpecialForm{
public:
    ReturnSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class BreakSF : public NodeSpecialForm{
public:
    BreakSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
};

class NodeParams : public NodeList {
public:
    NodeParams (NodeList* node){
        this->type = Params;
        this->terminal = false;
        this->tokenized_code = node->get_tokenized_code();
        this->interval = node->get_interval();
        this->bracket_info = node->get_bracket_info();
        this->index = node->get_index();
        this->children = node->children;
    }
    bool typecheck();
};

#endif