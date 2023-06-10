#include "list_funs.hpp"

int ListFun::p1_size() {
    NodeList *p1 = dynamic_cast < NodeList *>(params->children[1]);
    if(p1)
        return p1->children.size() - 2;
    return -1;
}

void ListFun::typecheck() {
}

void ListFun::strip(int idx) {
    if(params->children[idx]->type != SpecialForm)    
        print_error(" expecting a quoted list",6);
    string nm = dynamic_cast<NodeTerminal*>(params->children[idx]->children[1])->get_name();
    if(nm != "quote")
        print_error(" expecting a quoted list",6);
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[idx]->children[2]);
    params->children[idx] = p1;
}

void HeadFun::typecheck() {
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);
    if (!p1) {
        print_error(" function expecting list",5);
    }
    if(!p1_size()) {
        print_error(" Cannot perform operation on empty list",5);
    }
}

Node *HeadFun::run() {
    typecheck();
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);
    auto term = dynamic_cast<NodeTerminal *>(p1->children[1]);
    auto lit = dynamic_cast<NodeLiteral *>(p1->children[1]);

    if(lit) {
        term = dynamic_cast<NodeTerminal *>(lit->children[0]);
    }

    if(term) {
        return new NodeTerminal(*term);
    }

    auto lst = dynamic_cast<NodeList *>(p1->children[1]);

    if(lst) {
        return new NodeList(*lst);
    }
    exit(11);
}

void TailFun::typecheck() {
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);
    if (!p1) {
        print_error(" function expecting list",5);
    }
    if(!p1_size()) {
        print_error(" Cannot perform operation on empty list",5);
    }
}

Node* consturct_quote(NodeList *lst) {
    NodeTerminal* q = new NodeTerminal (
        lst->get_bracket_info(),
        lst->get_tokenized_code(),
        make_pair(lst->get_interval().first-1, lst->get_interval().first-1),
        keyword
    );
    NodeList *ret = new NodeList();
    vector <Node *> &children = ret->children;
    children.push_back(new NodeTerminal(
        lst->get_bracket_info(),
        lst->get_tokenized_code(), 
        make_pair(lst->get_interval().first, lst->get_interval().first), 
    lpar));
    children.push_back(q);
    children.push_back(lst);
    children.push_back(new NodeTerminal(
        lst->get_bracket_info(),
        lst->get_tokenized_code(), 
        make_pair(lst->get_interval().second, lst->get_interval().second), 
    rpar));
    return new QuoteSF(ret);
}

Node *TailFun::run() {
    typecheck();
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);
    NodeList *lst = new NodeList(*p1);
    lst->children.erase(lst->children.begin() + 1);
    return consturct_quote(lst);
}

void ConsFun::typecheck() {
    NodeList *p2 = dynamic_cast<NodeList *>(params->children[2]);
    if (!p2) {
        print_error(" function expecting list",5);
    }
    
}

Node *ConsFun::run() {
    typecheck();
    NodeList *p2 = dynamic_cast<NodeList *>(params->children[2]);

    NodeList *ret = new NodeList(*p2);
    ret->children.insert(ret->children.begin() + 1, params->children[1]);
    return consturct_quote(ret);
}

void IsEmptyFun::typecheck() {
    
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);
    if (!p1) {
        print_error(" function expecting list",5);
    }
}

Node *IsEmptyFun::run() {
    typecheck();
    NodeList *p1 = dynamic_cast<NodeList *>(params->children[1]);
    bool v = (p1_size() == 0);
    NodeTerminal *ret = new NodeTerminal {
        p1->get_bracket_info(),
        tokenized_code,
        p1->get_interval(),
        boolean,
        v
    };
    return ret;
}

void EvalFun::typecheck() {
}

Node *EvalFun::run() {
    return params->children[1];
}