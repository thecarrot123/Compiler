#ifndef SYNTAX_NODES_HEADER
#define SYNTAX_NODES_HEADER
#include <fstream>
#include <vector>
#include "token.hpp"
#include "node.hpp"

class NodeProgram : public Node {
public:
    NodeProgram() {
        type = Program;
        terminal = false;
    }

    NodeProgram(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Program;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    bool parse();
};

class NodeElement : public Node{
public:
    NodeElement() {
        type = Element;
        terminal = false;
    }

    NodeElement(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Element;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    bool parse();
    Node* get_child();
};

class NodeList : public Node{
public:
    NodeList() {
        type = List;
        terminal = false;
    }

    NodeList(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = List;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }
       
    //virtual bool typecheck();
    bool parse();
};

class NodeLiteral : public Node{
public:
    NodeLiteral() {
        type = Literal;
        terminal = false;
    }

    NodeLiteral(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Literal;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    bool parse();
};

class NodeAtom : public Node{
public:

    NodeAtom() {
        type = Atom;
        terminal = false;
    }

    NodeAtom(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Atom;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    bool parse();
    Node* get_child();
};


class NodeTerminal : public Node{

public:  
    NodeTerminal() {
        terminal = true;
    }

    NodeTerminal(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval, NodeType type){
        terminal = true;
        this->type = type;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }
};
#endif