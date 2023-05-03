#include "comparison_funs.hpp"

void ComparisonFun::typecheck() {
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    if (!p1 || !p2) {
        print_error(" function expecting integer, real, or bool",5);
    }
    if (p1->type != p2->type) {
        print_error(" function expecting equivalent types",5);
    }
}

double ComparisonFun::get_comparison_val(NodeTerminal *node) {
    if(node->type == integer)
        return get<int>(node->value);
    if(node->type == real)
        return get<double>(node->value);
    if(node->type == boolean)
        return get<bool>(node->value);
    if(node->type == null)
        return 0.0;
    print_error(" function expecting integer, real, or bool",5);
    return -1;
}

Node* EqualFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = (get_comparison_val(p1) == get_comparison_val(p2));
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* NonequalFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = (get_comparison_val(p1) != get_comparison_val(p2));
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* LessFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = (get_comparison_val(p1) < get_comparison_val(p2));
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* LesseqFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = (get_comparison_val(p1) <= get_comparison_val(p2));
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* GreaterFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = (get_comparison_val(p1) > get_comparison_val(p2));
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}

Node* GreatereqFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    bool val = (get_comparison_val(p1) >= get_comparison_val(p2));
    auto ret = new NodeTerminal(
        p2->get_bracket_info(),
        tokenized_code,
        make_pair(p1->get_interval().first,p2->get_interval().second),
        boolean,
        val
    );
    return ret;
}