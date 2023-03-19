#ifndef SYNTAX_NODE_HEADER
#define SYNTAX_NODE_HEADER
#include <fstream>
#include <vector>
#include "token.hpp"

enum Type{
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
    pair<int,int> interval;
    Type type;
    bool terminal;

public:
    void parse();
};

class NodeProgram : private Node {
    vector <Node*> children;
    
    NodeProgram(){
        type = Program;
        terminal = false;
    }

    NodeProgram(pair<int,int> interval) {
        this->interval = interval;
    }
};

class NodeElement : private Node{
    vector<Node*> children;

    NodeElement(){
        type = Element;
        terminal = false;
    }

    NodeElement(pair<int,int> interval) {
        this->interval = interval;
    }
};

class NodeList : private Node{
    vector<Node*> children;

    NodeList(){
        type = List;
        terminal = false;
    }

    NodeList(pair<int,int> interval) {
        this->interval = interval;
    }
};

class NodeList : private Node{
    vector<Node*> children;

    NodeList(){
        type = List;
        terminal = false;
    }

    NodeList(pair<int,int> interval) {
        this->interval = interval;
    }
};

class NodeLiteral : private Node{
    Node* child;

    NodeLiteral(){
        type = Literal;
        terminal = false;
    }

    NodeLiteral(pair<int,int> interval) {
        this->interval = interval;
    }
};

class NodeAtom : private Node{
    Node* child;

    NodeAtom(){
        type = Atom;
        terminal = false;
    }

    NodeAtom(pair<int,int> interval) {
        this->interval = interval;
    }
};

class NodeTerminal : private Node{
    
    NodeTerminal(){
        terminal = true;
    }

    NodeTerminal(Type type){
        this->type = type;
    }
};
#endif