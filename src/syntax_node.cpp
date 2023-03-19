#include "syntax_node.hpp"
#include "token.hpp"
#include <vector>
#include <stdio.h>
using namespace std;

void Node::set_type(NodeType type){
    this->type = type;
}

void Node::set_terminal(bool terminal){
    this->terminal = terminal;
}

bool NodeProgram::parse(){
    int l = interval.first;
    int r = interval.second;
    for (int i = l; i <= r; i++)
    {
        if (tokenized_code[i].type == LPAR){
            NodeElement newNode(make_pair(i, bracket_info[i]));
            children.push_back(newNode);
            i = bracket_info[i];
        }

        else if (tokenized_code[i].type == RPAR){
            return 0;
        }

        else{
            NodeElement newNode(make_pair(i, i));
            children.push_back(newNode);
        }
    }

    return 1;
}

bool NodeList::parse(){
    NodeTerminal firstNode(lpar);
    children.push_back(firstNode);

    int l = interval.first + 1;
    int r = interval.second - 1;
    for (int i = l; i <= r; i++)
    {
        if (tokenized_code[i].type == LPAR){
            NodeElement newNode(make_pair(i, bracket_info[i]));
            children.push_back(newNode);
            i = bracket_info[i];
        }

        else if (tokenized_code[i].type == RPAR){
            return 0;
        }

        else{
            NodeElement newNode(make_pair(i, i));
            children.push_back(newNode);
        }
    }

    NodeTerminal lastNode(rpar);
    children.push_back(lastNode);
    
    return 1;
}

// Might change later (no need to NodeAtom or NodeLiteral)
bool NodeElement::parse(){
    int l = interval.first;
    int r = interval.second;
    if (l != r){
        if (tokenized_code[l].type == LPAR){
            child = new NodeList(make_pair(l, r));
        }
        else
            return 0;
    }
    else{
        if (tokenized_code[l].type == ATOM || tokenized_code[l].type == KEYWORD)
            child = new NodeAtom(make_pair(l, r));
        else if (tokenized_code[l].type == REAL || tokenized_code[l].type == INT || tokenized_code[l].type == BOOL || tokenized_code[l].type == NUL)
            child = new NodeLiteral(make_pair(l, r));
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
    child = new NodeTerminal(type);
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
    child = new NodeTerminal(type);
    return 1;
}