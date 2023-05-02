#include "list_funs.hpp"

int ListFun::p1_size() {
    NodeList *p1 = dynamic_cast < NodeList *>(params->children[1]);
    if(p1)
        return p1->children.size() - 2;
}

void ListFun::typecheck() {
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);
    if (!p1) {
        print_error(this->name + " function expecting list",5);
    }
}

void HeadFun::typecheck() {
    ListFun::typecheck();
    if(!p1_size()) {
        print_error(this->name + " Cannot perform operation on empty list",5);
    }
}

Node *HeadFun::run() {
    typecheck();
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);

    auto term = dynamic_cast<NodeTerminal *>(p1->children[1]);

    if(term) {
        return term;
    }

    auto lst = dynamic_cast<NodeList *>(p1->children[1]);

    if(lst) {
        return lst;
    }
}

void TailFun::typecheck() {
    ListFun::typecheck();
    if(!p1_size()) {
        print_error(this->name + " Cannot perform operation on empty list",5);
    }
}

Node *TailFun::run() {
    typecheck();
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);

    NodeList *ret = new NodeList(*p1);
    ret->children.erase(ret->children.begin() + 1);
    return ret;
}

void ConsFun::typecheck() {
    
    NodeList *p2 = dynamic_cast<NodeList *>(params->children[2]);
    if (!p2) {
        print_error(this->name + " function expecting list",5);
    }
    
}

Node *ConsFun::run() {
    typecheck();
    NodeList *p2 = dynamic_cast<NodeList *>(params->children[2]);

    NodeList *ret = new NodeList(*p2);
    ret->children.insert(ret->children.begin() + 1, params->children[1]);
    return ret;
}

Node *IsEmptyFun::run() {
    typecheck();
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);

    NodeTerminal *ret = new NodeTerminal {
        p1->get_bracket_info(),
        tokenized_code,
        p1->get_interval(),
        integer,
        (p1_size() == 0)
    };
    return ret;
}