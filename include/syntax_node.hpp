#ifndef SYNTAX_NODE_HEADER
#define SYNTAX_NODE_HEADER
#include <fstream>
#include <vector>
#include "token.hpp"

enum NodeType{
    Program,
    Element,
    List,
    Literal,
    Atom,
    real,
    boolean,
    null,
    atom,
    lpar,
    rpar,
    keyword,
    integer
};

class Node {
protected:
    vector <Token> tokenized_code;
    int* bracket_info;
    pair<int,int> interval;
    NodeType type;
    bool terminal;

public:
    bool parse();
    void set_type(NodeType type);
    void set_terminal(bool terminal);
};

class NodeProgram : public Node {
    vector <Node> children;

public:
    NodeProgram() {
        type = Program;
        terminal = false;
    }

    NodeProgram(pair<int,int> interval) {
        this->interval = interval;
    }

    bool parse();
};

class NodeElement : public Node{
    Node* child;

public:
    NodeElement() {
        type = Element;
        terminal = false;
    }

    NodeElement(pair<int,int> interval) {
        this->interval = interval;
    }

    bool parse();
};

class NodeList : public Node{
    vector<Node> children;

public:
    NodeList() {
        type = List;
        terminal = false;
    }

    NodeList(pair<int,int> interval) {
        this->interval = interval;
    }

    bool parse();
};

class NodeLiteral : public Node{
    Node* child;

public:
    NodeLiteral() {
        type = Literal;
        terminal = false;
    }

    NodeLiteral(pair<int,int> interval) {
        this->interval = interval;
    }

    bool parse();
};

class NodeAtom : public Node{
    Node* child;

public:
    NodeAtom() {
        type = Atom;
        terminal = false;
    }

    NodeAtom(pair<int,int> interval) {
        this->interval = interval;
    }

    bool parse();
};

class NodeTerminal : public Node{

public:  
    NodeTerminal() {
        terminal = true;
    }

    NodeTerminal(NodeType type){
        this->type = type;
    }
};
#endif