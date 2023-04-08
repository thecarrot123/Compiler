#ifndef SIMANTIXER_HEADER
#define SIMANTIXER_HEADER
#include "semantic_nodes.hpp"
#include <map>

class Semantixer{
private:
    Node* root;
    bool error = 0;
    vector < string > error_messages;
    map <string, Node*> param_table;
    map <string, Node*> body_table;

public:
    Semantixer(Node *root){
        this-> root = root;
    }

    Node* traverse();

    void first_traversal(Node* node);
    void second_traversal(Node* node, bool param_flag);
    void third_traversal(Node* node);

    void print(string filename);
    void print(ostream& fout, Node* node);
};

#endif