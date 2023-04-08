#include "semantixer.hpp"
#include <iostream>

Node* Semantixer::traverse(){
    first_traversal(root);
    second_traversal(root, false);
    third_traversal(root);
    return root;
}


void Semantixer::first_traversal(Node* node){
    if (node->isTerminal())
        return;
    for (auto &next_node: node->children){
        auto temp = next_node;
        NodeElement* node_element = dynamic_cast<NodeElement*>(next_node);
        if (node_element){
            next_node = node_element->get_child();
            delete temp;
            temp = next_node;
            NodeAtom* node_atom = dynamic_cast<NodeAtom*>(next_node);
            if (node_atom){
                next_node = node_atom->get_child();
                delete temp;
            }
        }
        first_traversal(next_node);
    }
}

void Semantixer::second_traversal(Node* node, bool param_flag){
    bool _param_flag = false;
    for (auto &next_node: node->children){
        NodeList* node_list = dynamic_cast<NodeList*>(next_node);
        if (node_list){
            Node* first_arg = next_node->children[1];
            if (first_arg->type == keyword){
                string token = first_arg->get_tokenized_code()[first_arg->get_interval().first+1].content;
                if (token == "quote"){
                    next_node = new QuoteSF(node_list);
                }
                else if (token == "setq"){
                    next_node = new SetqSF(node_list);
                }
                else if (token == "func"){
                    _param_flag = true;
                    next_node = new FuncSF(node_list);
                }
                else if (token == "lambda"){
                    _param_flag = true;
                    next_node = new LambdaSF(node_list);
                }
                else if (token == "prog"){
                    _param_flag = true;
                    next_node = new ProgSF(node_list);
                }
                else if (token == "cond"){
                    next_node = new CondSF(node_list);
                }
                else if (token == "while"){
                    next_node = new WhileSF(node_list);
                }
                else if (token == "return"){
                    next_node = new ReturnSF(node_list);
                }
                else if (token == "break"){
                    next_node = new BreakSF(node_list);
                }
            }
            else if (param_flag){
                bool flag = true;
                for (int i = 1 ; i < next_node->children.size() - 1; i++){
                    if (next_node->children[i]->type != atom)
                        flag = false;
                }
                if (flag){
                    next_node = new NodeParams(node_list);
                }
            }
        }
        second_traversal(next_node, _param_flag);
    }
}

void Semantixer::third_traversal(Node* node){
    for (auto& next_node: node->children){
        NodeSpecialForm* nodeSF = dynamic_cast<NodeSpecialForm*>(next_node);
        if (nodeSF){
            if (!nodeSF->typecheck()){
                error = 1;
                error_messages.push_back("Error: Wrong usage of a special form at line " + 
                    to_string(nodeSF->get_tokenized_code()[nodeSF->get_interval().first + 1].line));
            }
        }
        third_traversal(next_node);
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