#ifndef SYNTAX_NODES_HEADER
#define SYNTAX_NODES_HEADER
#include <fstream>
#include <vector>
#include <variant>
#include "token.hpp"
#include "node.hpp"
class NodeProgram : public Node {
public:
    NodeProgram() {
        type = Program;
        terminal = false;
    }

    NodeProgram(NodeProgram const& other) : Node(other){};

    NodeProgram(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Program;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    Node* clone();
    bool parse();
};

class NodeElement : public Node{
public:
    NodeElement() {
        type = Element;
        terminal = false;
    }

    NodeElement(NodeElement const& other) : Node(other){};
    
    NodeElement(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Element;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    Node* clone();
    bool parse();
    Node* get_child();
};

class NodeList : public Node{
public:
    NodeList() {
        type = List;
        terminal = false;
    }

    NodeList(NodeList const& other) : Node(other){};
    NodeList(Node const& other) : Node(other){};

    NodeList(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = List;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }
    
    Node* clone();
    bool parse();
};

class NodeLiteral : public Node{
public:
    NodeLiteral() {
        type = Literal;
        terminal = false;
    }

    NodeLiteral(NodeLiteral const& other) : Node(other){};

    NodeLiteral(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Literal;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    Node* clone();
    bool parse();
};

class NodeAtom : public Node{
public:

    NodeAtom() {
        type = Atom;
        terminal = false;
    }

    NodeAtom(NodeAtom const& other) : Node(other){};

    NodeAtom(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval) {
        type = Atom;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    Node* clone();
    bool parse();
    Node* get_child();
};


class NodeTerminal : public Node{

public:
    variant < double, int, bool, nullptr_t> value;
    NodeTerminal() {
        terminal = true;
    }

    NodeTerminal(NodeTerminal const& other) : Node(other){
        value = other.value;
    };

    NodeTerminal(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval, NodeType type){
        terminal = true;
        this->type = type;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
        this->interval = interval;
        init_value();
    }

    NodeTerminal(int* bracket_info, vector <Token> &tokenized_code, pair<int,int> interval, NodeType type, variant < double, int, bool, nullptr_t > value){
        terminal = true;
        this->type = type;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
        this->interval = interval;
        this->value = value;
    }

    void init_value();
    string get_name();
    Node* clone();
};
#endif