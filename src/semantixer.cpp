#include "semantixer.hpp"
#include <iostream>

Node* Semantixer::first_traverse(){
    first_traverse(root);
    return root;
}

void Semantixer::first_traverse(Node* node){
    if (node->isTerminal())
        return;
    for (auto &next_node: node->children){
        NodeElement* node_element = dynamic_cast<NodeElement*>(next_node);
        if (node_element){
            next_node = node_element->get_child();
            NodeAtom* node_atom = dynamic_cast<NodeAtom*>(next_node);
            if (node_atom){
                next_node = node_atom->get_child();
            }
        }
        NodeList* node_list = dynamic_cast<NodeList*>(next_node);
        
        first_traverse(next_node);
    }
}

void Semantixer::print(ostream& fout, Node* node){
    fout << node->get_index() <<"[label=\""<< node->get_type() <<"\"]\n";
    for (int i = 0; i < node->children.size(); i++){
        Node* next_node = node->children[i];
        fout << node->get_index() <<" -- " <<next_node->get_index()<<"\n";
        print(fout, next_node);
    }
}

void Semantixer::print(string filename) {
    filebuf file;
    file.open(filename, ios::out);
    ostream fout(&file);
    fout << "graph {\n";
    print(fout, root);
    fout<<'}';
    file.close();
}