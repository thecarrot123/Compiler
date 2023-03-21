#ifndef SYNTAXER_HEADER
#define SYNTAXER_HEADER
#include "token.hpp"
#include "syntax_node.hpp"
#include <vector>
#include <cstring>


using namespace std;

class Syntaxer {
private:
    vector < Token > &tokenized_code;
    vector < string > error_messages;
    int tree_size = 0;
    int *bracket_info;
    bool error = 0;
    bool check_brackets();
    int size() {
        return tokenized_code.size();
    }

public:
    Syntaxer(vector < Token > *code) : tokenized_code(*code){
        this->bracket_info = new int[tokenized_code.size()];
        memset(bracket_info,-1,4*size());
        this->check_brackets();
    }

    Node* get_root();

    void parse_code(Node* node);
    void print();
    void print(string filename, Node* root);
    void print(ostream& fout, Node* node);
    void print_errors();
};

#endif