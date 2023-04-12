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
    int prog_count = 0;

public:
    Semantixer(Node *root){
        this-> root = root;
    }

    Node* traverse();

    void preprocessing();
    void first_traversal(Node* node);
    void second_traversal(Node* node, bool param_flag);
    void third_traversal(Node* node);
    void forth_traversal(Node* node);
    void add_to_body_table(string atom, Node* value, int line);
    void add_params(NodeParams* params);
    void remove_local_context(NodeParams* params);

    void print(string filename);
    void print(ostream& fout, Node* node);
    void print_errors();
};

#endif