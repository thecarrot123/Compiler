#include "arithmetic_funs.hpp"

void ArithmeticFun::typecheck() {
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    if (!p1 || p1->type == boolean || p1->type == null) {
        print_error(" function expecting integer or real",5);
    }
    if (!p2 || p2->type == boolean || p1->type == null) {
        print_error(" function expecting integer or real",5);
    }
}

double ArithmeticFun::get_arithmetic_val( NodeTerminal *node) {
    if(node->type == integer)
        return get<int>(node->value);
    if(node->type == real)
        return get<double>(node->value);
    print_error(" function expecting integer or real",5);
    return -1;
}

Node* PlusFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;

    if (p1->type == integer && p2->type == integer){
        int val = get_arithmetic_val(p1) + get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            integer,
            val
        );
        return ret;
    }
    else{
        double val = get_arithmetic_val(p1) + get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            real,
            val
        );
        return ret;
    }
}

Node* MinusFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    if (p1->type == integer && p2->type == integer){
        int val = get_arithmetic_val(p1) - get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            integer,
            val
        );
        return ret;
    }
    else{
        double val = get_arithmetic_val(p1) - get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            real,
            val
        ); 
        return ret;
    }
}

Node* TimesFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    if (p1->type == integer && p2->type == integer){
        int val = get_arithmetic_val(p1) * get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            integer,
            val
        );
        return ret;
    }
    else{
        double val = get_arithmetic_val(p1) * get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            real,
            val
        ); 
        return ret;
    }
}

void DivideFun::typecheck() {
    ArithmeticFun::typecheck();
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    if (get_arithmetic_val(p2) == 0) {
        print_error("Dividing on 0",5);
    }
}

Node* DivideFun::run() {
    typecheck();
    NodeTerminal *p1 = dynamic_cast<NodeTerminal *>(params->children[1]);
    NodeTerminal *p2 = dynamic_cast<NodeTerminal *>(params->children[2]);
    NodeType type;
    if (p1->type == integer && p2->type == integer){
        int val = get_arithmetic_val(p1) / get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            integer,
            val
        );
        return ret;
    }
    else{
        double val = get_arithmetic_val(p1) / get_arithmetic_val(p2);
        auto ret = new NodeTerminal(
            p2->get_bracket_info(),
            tokenized_code,
            make_pair(p1->get_interval().first,p2->get_interval().second),
            real,
            val
        ); 
        return ret;
    }
}