#ifndef SEMANTIC_NODES_HEADER
#define SEMANTIC_NODES_HEADER
#include "node.hpp"
#include "syntax_nodes.hpp"
#include <iostream>

class NodeSpecialForm : public NodeList {
public:

    NodeSpecialForm(NodeSpecialForm const& other) : NodeList(other){};

    NodeSpecialForm(NodeList* node){
        this->type = SpecialForm;
        this->terminal = false;
        this->tokenized_code = node->get_tokenized_code();
        this->interval = node->get_interval();
        this->bracket_info = node->get_bracket_info();
        this->index = node->get_index();
        this->children = node->children;
    }
    virtual bool typecheck() = 0;
};

class QuoteSF : public NodeSpecialForm{
public:
    QuoteSF(QuoteSF const& other) : NodeSpecialForm(other){};
    QuoteSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class SetqSF : public NodeSpecialForm{
public:
    SetqSF(SetqSF const& other) : NodeSpecialForm(other){};
    SetqSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class FuncSF : public NodeSpecialForm{
public:
    FuncSF(FuncSF const& other) : NodeSpecialForm(other){};
    FuncSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class LambdaSF : public NodeSpecialForm{
public:
    LambdaSF(LambdaSF const& other) : NodeSpecialForm(other){};
    LambdaSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class ProgSF : public NodeSpecialForm{
public:
    ProgSF(ProgSF const& other) : NodeSpecialForm(other){};
    ProgSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class CondSF : public NodeSpecialForm{
public:
    CondSF(CondSF const& other) : NodeSpecialForm(other){};
    CondSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class WhileSF : public NodeSpecialForm{
public:
    WhileSF(WhileSF const& other) : NodeSpecialForm(other){};
    WhileSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class ReturnSF : public NodeSpecialForm{
public:
    ReturnSF(ReturnSF const& other) : NodeSpecialForm(other){};
    ReturnSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class BreakSF : public NodeSpecialForm{
public:
    BreakSF(BreakSF const& other) : NodeSpecialForm(other){};
    BreakSF(NodeList* node): NodeSpecialForm(node){}
    bool typecheck();
    Node* clone();
};

class NodeParams : public NodeList {
public:
    NodeParams(NodeParams const& other) : NodeList(other){};
    NodeParams (NodeList* node){
        this->type = Params;
        this->terminal = false;
        this->tokenized_code = node->get_tokenized_code();
        this->interval = node->get_interval();
        this->bracket_info = node->get_bracket_info();
        this->index = node->get_index();
        this->children = node->children;
    }
    Node* clone();
};

#endif