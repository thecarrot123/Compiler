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
    static const string node_types[];

public:
    vector <Node*> children;
    virtual bool parse();
    bool isTerminal();
    virtual string get_type();
};

class NodeProgram : public Node {
public:
    NodeProgram() {
        type = Program;
        terminal = false;
    }

    NodeProgram(int* bracket_info, vector <Token> tokenized_code, pair<int,int> interval) {
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

    NodeElement(int* bracket_info, vector <Token> tokenized_code, pair<int,int> interval) {
        type = Element;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    bool parse();
};

class NodeList : public Node{
public:
    NodeList() {
        type = List;
        terminal = false;
    }

    NodeList(int* bracket_info, vector <Token> tokenized_code, pair<int,int> interval) {
        type = List;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    bool parse();
};

class NodeLiteral : public Node{
public:
    NodeLiteral() {
        type = Literal;
        terminal = false;
    }

    NodeLiteral(int* bracket_info, vector <Token> tokenized_code, pair<int,int> interval) {
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

    NodeAtom(int* bracket_info, vector <Token> tokenized_code, pair<int,int> interval) {
        type = Atom;
        terminal = false;
        this->interval = interval;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }

    bool parse();
};

class NodeTerminal : public Node{

public:  
    NodeTerminal() {
        terminal = true;
    }

    NodeTerminal(int* bracket_info, vector <Token> tokenized_code, NodeType type){
        terminal = true;
        this->type = type;
        this->tokenized_code = tokenized_code;
        this->bracket_info = bracket_info;
    }
};
#endif