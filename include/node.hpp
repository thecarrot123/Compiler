#ifndef NODE_HEADER
#define NODE_HEADER
#include "token.hpp"
#include <vector>
#include <map>

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
    integer,
    SpecialForm,
    Params,
};


class Node {
protected:
    vector <Token> tokenized_code;
    int* bracket_info;
    pair<int,int> interval;
    bool terminal;
    static const string node_types[];
    int index;

public:
    NodeType type;
    vector <Node*> children;
    map <string, Node*> param_table;
    map <string, Node*> body_table;
    Node (){}
    Node (Node const &other){
        this->tokenized_code = other.tokenized_code;
        this->bracket_info = other.bracket_info;
        this->terminal = other.terminal;
        this->index = other.index;
        this->type = other.type;
        for (int i = 0; i < other.children.size(); i++){
            this->children.push_back(other.children[i]->clone());
        }
    }
    virtual Node* clone();
    virtual bool parse();
    bool isTerminal();
    virtual string get_type();
    virtual int get_index();
    virtual void set_index(int index);
    vector <Token> get_tokenized_code();
    pair<int,int> get_interval();
    int* get_bracket_info();
};

#endif