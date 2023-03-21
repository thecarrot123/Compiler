#include "syntaxer.hpp"
#include "syntax_node.hpp"
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
        //printf("Error: Unclosed parentheses at line %d\n",tokenized_code[parentheses.top()].line);
        parentheses.pop();
    }
    /*
    for(int i=0;i<size();i++) {
        if(bracket_info[i] != -1) {
            printf("%d: %d\n",i,bracket_info[i]);
        }
    }*/
    return !error;
}

pair<vector<Node*>, vector<vector<int>> > Syntaxer::parse_code(){
    queue<pair<Node*,int> > bfs;
    bfs.push(make_pair(new NodeProgram(bracket_info, tokenized_code, make_pair(0, size())), -1));
    while (!bfs.empty()){
        int index = nodes_list.size();
        nodes_list.push_back(bfs.front().first);
        if (bfs.front().second >= 0){
            tree[bfs.front().second].push_back(index);
        }
        bfs.pop();
        if (nodes_list.back()->isTerminal()){
            continue;
        }
        if (nodes_list.back()->parse())
        {
            for(int i = 0; i < nodes_list.back()->children.size(); i++){
                bfs.push(make_pair(nodes_list.back()->children[i], index));
            }
        }
        else
        {
            //error
        }
    }
    return make_pair(nodes_list, tree);
}

void Syntaxer::print(){
    cout << "graph {\n";
    for (int i = 0 ; i < nodes_list.size(); i++){
        cout << i <<"[label=\""<< nodes_list[i]->get_type() <<"\"]\n";
    }
    cout <<endl;

    for (int i = 0; i < nodes_list.size(); i++){
        for (int j = 0; j < tree[i].size();j++)
            cout << i <<" -- " <<tree[i][j]<<"\n";
    }
    cout<<'}';
}

void Syntaxer::print(string filename) {
    filebuf file;
    file.open(filename, ios::out);
    ostream ffout(&file);
    ffout << "graph {\n";
    for (int i = 0 ; i < nodes_list.size(); i++){
        ffout << i <<"[label=\""<< nodes_list[i]->get_type() <<"\"]\n";
    }
    ffout <<endl;

    for (int i = 0; i < nodes_list.size(); i++){
        for (int j = 0; j < tree[i].size();j++)
            ffout << i <<" -- " <<tree[i][j]<<"\n";
    }
    ffout<<'}';
    file.close();
}