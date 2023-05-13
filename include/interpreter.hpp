#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER
#include <semantic_nodes.hpp>

class Interpreter{
private:
    Node* root;
    Node* param_root;
    map<string, Node*> context;
    string ans = "";
public:
    Interpreter(Node *root){
        this->root = root;
    }
    Interpreter(Node *root, Node* param_root){
        this->root = root;
        this->param_root = param_root;
    }
    bool ispredefined(Node *node);
    Node* reduce(Node *node);
    Node* expand(Node *node);
    void interpret();
    void print_error(string error_message, int error_number);
    void print_code(Node* node);
    void print(string filename);
    void print(ostream& fout, Node* node);
};
#endif