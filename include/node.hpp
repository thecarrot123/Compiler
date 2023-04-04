#ifndef NODE_HEADER
#define NODE_HEADER
#include "token.hpp"
#include <vector>

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
    virtual bool parse();
    //virtual bool traverse();
    bool isTerminal();
    virtual string get_type();
    virtual int get_index();
    virtual void set_index(int index);
};

#endif