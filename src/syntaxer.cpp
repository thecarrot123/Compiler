#include "syntaxer.hpp"
#include "syntax_nodes.hpp"
#include "token.hpp"
#include <stack>
#include <stdio.h>
#include <queue>
#include <iostream>
#include <fstream>


using namespace std;

stack < int > parentheses;

bool Syntaxer::check_brackets(){
    for(int i=0;i<size();i++) {
        if(tokenized_code[i].type == token_type::LPAR)
            parentheses.push(i);
        if(tokenized_code[i].type == token_type::RPAR) {
            if(parentheses.size()) {
                int j = parentheses.top();
                bracket_info[j] = i;
                bracket_info[i] = j;
                parentheses.pop();
            }
            else {
                error = 1;
                error_messages.push_back("Error: Unopened parentheses at line " + 
                    to_string(tokenized_code[i].line));
            }
        }
    }
    while(parentheses.size()) {
        error = 1;
        error_messages.push_back("Error: Unclosed parentheses at line " + 
            to_string(tokenized_code[parentheses.top()].line));
        parentheses.pop();
    }
    return !error;
}

Node* Syntaxer::get_root(){
    if (error){
        return NULL;
    }
    Node* root = new NodeProgram(bracket_info, tokenized_code, make_pair(0, (int)size() - 1));
    root->set_index(0);
    tree_size++;
    parse_code(root);
    if (error)
        return NULL;
    return root;
}

void Syntaxer::parse_code(Node* node){
    if (node->isTerminal())
        return;
    if (node->parse()){
        for (int i = 0; i < node->children.size(); i++){
            Node* next_node = node->children[i];
            next_node->set_index(tree_size++);
            parse_code(next_node);
        }
    }
    else{
        error = 1;
        error_messages.push_back("Error while parsing a " + node->get_type());
        return;
    }
}

void Syntaxer::print(ostream& fout, Node* node){
    fout << node->get_index() <<"[label=\""<< node->get_type() <<"\"]\n";
    for (int i = 0; i < node->children.size(); i++){
        Node* next_node = node->children[i];
        fout << node->get_index() <<" -- " <<next_node->get_index()<<"\n";
        print(fout, next_node);
    }
}

void Syntaxer::print(string filename, Node* root) {
    filebuf file;
    file.open(filename, ios::out);
    ostream fout(&file);
    fout << "graph {\n";
    print(fout, root);
    fout<<'}';
    file.close();
}

void Syntaxer::print(Node* root) {
    cout << "graph {\n";
    print(cout, root);
    cout<<'}';
}

void Syntaxer::print_errors(){
    cout << "Syntax error(s):\n";
    for (int i = 0; i < error_messages.size(); i++){
        cout << error_messages[i] << '\n';
    }
}