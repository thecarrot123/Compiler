#include "syntax_node.hpp"
#include "token.hpp"
#include <vector>
#include <stdio.h>
using namespace std;

const string Node::node_types[] = {"Program", "Element", "List",  "Literal",  "Atom",  "real", "boolean", "null", 
                                "atom", "lpar", "rpar", "keyword", "integer"};

bool Node::isTerminal(){
    return terminal;
}

bool Node::parse(){
    return 0;
}

string Node::get_type(){
    return node_types[type];
}

bool NodeProgram::parse(){
    int l = interval.first;
    int r = interval.second;
    for (int i = l; i <= r; i++)
    {
        if (tokenized_code[i].type == LPAR){
            children.push_back(new NodeElement(bracket_info, tokenized_code, make_pair(i, bracket_info[i])));
            i = bracket_info[i];
        }

        else if (tokenized_code[i].type == RPAR){
            return false;
        }

        else{
            children.push_back(new NodeElement(bracket_info, tokenized_code, make_pair(i, i)));
        }
    }

    return true;
}

bool NodeList::parse(){
    children.push_back(new NodeTerminal(bracket_info, tokenized_code, lpar));

    int l = interval.first + 1;
    int r = interval.second - 1;
    for (int i = l; i <= r; i++)
    {
        if (tokenized_code[i].type == LPAR){
            children.push_back(new NodeElement (bracket_info, tokenized_code, make_pair(i, bracket_info[i])));
            i = bracket_info[i];
        }

        else if (tokenized_code[i].type == RPAR){
            return 0;
        }

        else{
            children.push_back(new NodeElement(bracket_info, tokenized_code, make_pair(i, i)));
        }
    }

    children.push_back(new NodeTerminal(bracket_info, tokenized_code, rpar));
    
    return 1;
}

// Might change later (no need to NodeAtom or NodeLiteral)
bool NodeElement::parse(){
    int l = interval.first;
    int r = interval.second;
    if (l != r){
        if (tokenized_code[l].type == LPAR){
            children.push_back(new NodeList(bracket_info, tokenized_code, make_pair(l, r)));
        }
        else
            return 0;
    }
    else{
        if (tokenized_code[l].type == ATOM || tokenized_code[l].type == KEYWORD)
            children.push_back(new NodeAtom(bracket_info, tokenized_code, make_pair(l, r)));
        else if (tokenized_code[l].type == REAL || tokenized_code[l].type == INT || tokenized_code[l].type == BOOL || tokenized_code[l].type == NUL)
            children.push_back(new NodeLiteral(bracket_info, tokenized_code, make_pair(l, r)));
        else
            return 0;
    }

    return 1;
}

bool NodeLiteral::parse(){
    int l = interval.first;
    int r = interval.second;
    if (l != r)
        return 0;
    NodeType type;
    if (tokenized_code[l].type == REAL)
        type = real;
    else if (tokenized_code[l].type == INT)
        type = integer;
    else if (tokenized_code[l].type == BOOL)
        type = boolean;
    else if (tokenized_code[l].type == NUL)
        type = null;
    children.push_back(new NodeTerminal(bracket_info, tokenized_code, type));
    return 1;
}

bool NodeAtom::parse(){
    int l = interval.first;
    int r = interval.second;
    if (l != r)
        return 0;
    NodeType type;
    if (tokenized_code[l].type == ATOM)
        type = atom;
    if (tokenized_code[l].type == KEYWORD)
        type = keyword;
    children.push_back(new NodeTerminal(bracket_info, tokenized_code, type));
    return 1;
}