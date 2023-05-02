#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER
#include <semantic_nodes.hpp>

class Interpreter{
private:
    Node* root;
public:
    Interpreter(Node *root){
        this->root = root;
    }

    Node* reduce(Node *node);
    Node* expand(Node *node);
    void print_error(string error_message, int error_number);
};
#endif