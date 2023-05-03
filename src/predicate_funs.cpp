#include "predicate_funs.hpp"


void PredicateFun::typecheck() {
    return;
}

NodeType PredicateFun::get_predicate_val(Node *node) {
    return node->type;
}

Node* IsIntFun::run() {
    typecheck();
    Node *p1 = params->children[1];
    bool val = (get_predicate_val(p1) == integer);
    auto ret = new NodeTerminal(
        p1->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p1->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* IsRealFun::run() {
    typecheck();
    Node *p1 = params->children[1];
    bool val = (get_predicate_val(p1) == real);
    auto ret = new NodeTerminal(
        p1->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p1->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* IsBoolFun::run() {
    typecheck();
    Node *p1 = params->children[1];
    bool val = (get_predicate_val(p1) == boolean);
    auto ret = new NodeTerminal(
        p1->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p1->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* IsNullFun::run() {
    typecheck();
    Node *p1 = params->children[1];
    bool val = (get_predicate_val(p1) == null);
    auto ret = new NodeTerminal(
        p1->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p1->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* IsAtomFun::run() {
    typecheck();
    Node *p1 = params->children[1];
    bool val = (get_predicate_val(p1) == atom);
    auto ret = new NodeTerminal(
        p1->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p1->get_interval().second),
        boolean,
        val
    );
    return ret;
}


Node* IsListFun::run() {
    typecheck();
    Node *p1 = params->children[1];
    bool val = (dynamic_cast<NodeList *>(p1) != NULL);
    auto ret = new NodeTerminal(
        p1->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p1->get_interval().second),
        boolean,
        val
    );
    return ret;
}
