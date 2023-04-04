#ifndef SIMANTIXER_HEADER
#define SIMANTIXER_HEADER
#include "semantic_nodes.hpp"


class Semantixer{
private:
    Node* root;
    bool error = 0;
    vector < string > error_messages;

public:
    Semantixer(Node *root){
        this-> root = root;
    }

    Node* first_traverse();
    void first_traverse(Node* node);

    void print(string filename);
    void print(ostream& fout, Node* node);
};

#endif