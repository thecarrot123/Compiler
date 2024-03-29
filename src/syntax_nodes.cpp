#include "syntax_nodes.hpp"
#include "token.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace std;

const string Node::node_types[] = {"Program", "Element", "List",  "Literal",  "Atom",  "real", "boolean", "null", 
                                "atom", "lpar", "rpar", "keyword", "integer","SpecialForm","Params", "Body"};

bool Node::isTerminal(){
    return terminal;
}

bool Node::parse(){
    return 0;
}

string Node::get_type(){
    return node_types[type];
}

int Node::get_index(){
    return (long long)this;
}

vector <Token>& Node::get_tokenized_code(){
    return tokenized_code;
}

pair<int,int> Node::get_interval(){
    return interval;
}

int* Node::get_bracket_info(){
    return bracket_info;
}

void Node::set_index(int index){
    this->index = index;
}

Node* NodeElement::get_child(){
        return children[0];
}

Node* NodeAtom::get_child(){
        return children[0];
}

Node* NodeProgram::clone(){
    return new NodeProgram(*this);
}

Node* NodeElement::clone(){
    return new NodeElement(*this);
}

Node* NodeList::clone(){
    return new NodeList(*this);
}

Node* NodeLiteral::clone(){
    return new NodeLiteral(*this);
}

Node* NodeAtom::clone(){
    return new NodeAtom(*this);
}

Node* NodeTerminal::clone(){
    return new NodeTerminal(*this);
}

Node* Node::clone(){
    return new Node(*this);
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
    int l = interval.first;
    int r = interval.second;

    children.push_back(new NodeTerminal(bracket_info, tokenized_code, make_pair(l, l), lpar));
    for (int i = l + 1; i <= r - 1; i++)
    {
        if (tokenized_code[i].type == LPAR){
            children.push_back(new NodeElement (bracket_info, tokenized_code, make_pair(i, bracket_info[i])));
            i = bracket_info[i];
        }

        else if (tokenized_code[i].type == RPAR){
            return false;
        }

        else{
            children.push_back(new NodeElement(bracket_info, tokenized_code, make_pair(i, i)));
        }
    }
    children.push_back(new NodeTerminal(bracket_info, tokenized_code, make_pair(r, r), rpar));
    return true;
}

bool NodeElement::parse(){
    int l = interval.first;
    int r = interval.second;
    if (l != r){
        if (tokenized_code[l].type == LPAR){
            children.push_back(new NodeList(bracket_info, tokenized_code, make_pair(l, r)));
        }
        else
            return false;
    }
    else{
        if (tokenized_code[l].type == ATOM || tokenized_code[l].type == KEYWORD)
            children.push_back(new NodeAtom(bracket_info, tokenized_code, make_pair(l, r)));
        else if (tokenized_code[l].type == REAL || tokenized_code[l].type == INT || tokenized_code[l].type == BOOL || tokenized_code[l].type == NUL)
            children.push_back(new NodeLiteral(bracket_info, tokenized_code, make_pair(l, r)));
        else
            return false;
    }

    return true;
}

bool NodeLiteral::parse(){
    int l = interval.first;
    int r = interval.second;
    if (l != r)
        return false;
    NodeType type;
    if (tokenized_code[l].type == REAL)
        type = real;
    else if (tokenized_code[l].type == INT)
        type = integer;
    else if (tokenized_code[l].type == BOOL)
        type = boolean;
    else if (tokenized_code[l].type == NUL)
        type = null;
    children.push_back(new NodeTerminal(bracket_info, tokenized_code, interval, type));
    return true;
}

bool NodeAtom::parse(){
    int l = interval.first;
    int r = interval.second;
    if (l != r)
        return false;
    NodeType type;
    if (tokenized_code[l].type == ATOM)
        type = atom;
    if (tokenized_code[l].type == KEYWORD)
        type = keyword;
    children.push_back(new NodeTerminal(bracket_info, tokenized_code, interval,type));
    return true;
}

void NodeTerminal::init_value(){
    if (type == boolean)
        value = (tokenized_code[interval.first].content == "true");
    else if (type == integer)
        value = stoi(tokenized_code[interval.first].content);
    else if (type == real)
        value = stod(tokenized_code[interval.first].content);
    else
        value = nullptr;
}

string NodeTerminal::get_name(){
    return tokenized_code[interval.first].content;
}