#include "logical_funs.hpp"

void LogicalFun::typecheck() {
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    if (!p1 || !p2) {
        print_error(" function expecting bool",5);
    }
    if (p1->type != boolean || p2->type != boolean) {
        print_error(" function expecting bool",5);
    }
}

bool LogicalFun::get_logical_val(NodeTerminal *node) {
    return get<bool>(node->value);
}

Node* AndFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = get_logical_val(p1) & get_logical_val(p2);
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* OrFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = get_logical_val(p1) | get_logical_val(p2);
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* XorFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = get_logical_val(p1) ^ get_logical_val(p2);
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

void NotFun::typecheck() {
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    if (!p1 || p1->type != boolean) {
        print_error(" function expecting bool",5);
    }
}

Node* NotFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeType type;
    bool val = !get_logical_val(p1);
    auto ret = new NodeTerminal(
        p1->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p1->get_interval().second),
        boolean,
        val
    );
    return ret;
}
