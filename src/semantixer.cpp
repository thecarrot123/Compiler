#include "semantixer.hpp"
#include <iostream>

Node* Semantixer::traverse(){
    preprocessing();
    first_traversal(root);
    second_traversal(root, false);
    third_traversal(root);
    if (!dynamic_cast<ProgSF*>(root->children.back()) && prog_flag){
        error = 1;
        error_messages.push_back("Error: Prog should be the last definition.");
    }
    if (prog_count != 1 && prog_flag){
        error = 1;
        error_messages.push_back("Error: There can be one and only one definition of prog.");
    }
    forth_traversal(root);
    if (error)
        return NULL;
    return root;
}

void Semantixer::preprocessing(){
    int *a;
    vector<Token> vec;
    NodeList *trash = new NodeList(a,vec,make_pair(0,0));
    trash->children.push_back(new Node);
    trash->children.push_back(new Node);
    trash->children.push_back(new Node);
    trash->children.push_back(new Node);
    param_table["plus"] = new NodeParams(trash);
    body_table["plus"] = new Node;
    param_table["minus"] = new NodeParams(trash);
    body_table["minus"] = new Node;
    param_table["times"] = new NodeParams(trash);
    body_table["times"] = new Node;
    param_table["divide"] = new NodeParams(trash);
    body_table["divide"] = new Node;
    param_table["cons"] = new NodeParams(trash);
    body_table["cons"] = new Node;
    param_table["equal"] = new NodeParams(trash);
    body_table["equal"] = new Node;
    param_table["nonequal"] = new NodeParams(trash);
    body_table["nonequal"] = new Node;
    param_table["less"] = new NodeParams(trash);
    body_table["less"] = new Node;
    param_table["lesseq"] = new NodeParams(trash);
    body_table["lesseq"] = new Node;
    param_table["greater"] = new NodeParams(trash);
    body_table["greater"] = new Node;
    param_table["greatereq"] = new NodeParams(trash);
    body_table["greatereq"] = new Node;
    param_table["and"] = new NodeParams(trash);
    body_table["and"] = new Node;
    param_table["or"] = new NodeParams(trash);
    body_table["or"] = new Node;
    param_table["xor"] = new NodeParams(trash);
    body_table["xor"] = new Node;
    trash->children.pop_back();
    param_table["head"] = new NodeParams(trash);
    body_table["head"] = new Node;
    param_table["tail"] = new NodeParams(trash);
    body_table["tail"] = new Node;
    param_table["isempty"] = new NodeParams(trash);
    body_table["isempty"] = new Node;
    param_table["isint"] = new NodeParams(trash);
    body_table["isint"] = new Node;
    param_table["isreal"] = new NodeParams(trash);
    body_table["isreal"] = new Node;
    param_table["isbool"] = new NodeParams(trash);
    body_table["isbool"] = new Node;
    param_table["isnull"] = new NodeParams(trash);
    body_table["isnull"] = new Node;
    param_table["isatom"] = new NodeParams(trash);
    body_table["isatom"] = new Node;
    param_table["islist"] = new NodeParams(trash);
    body_table["islist"] = new Node;
    param_table["not"] = new NodeParams(trash);
    body_table["not"] = new Node;
    param_table["eval"] = new NodeParams(trash);
    body_table["eval"] = new Node;
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
    for (auto &next_node: node->children){
        bool _param_flag = 0;
        NodeList* node_list = dynamic_cast<NodeList*>(next_node);
        if (node_list){
            Node* first_arg = next_node->children[1];
            if (first_arg->type == keyword){
                string token = first_arg->get_tokenized_code()[first_arg->get_interval().first].content;
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
                for (int i = 1 ; i < next_node->children.size() - 1 ; i++){
                    if (next_node->children[i]->type != atom)
                        flag = false;
                }
                if (flag){
                    next_node = new NodeParams(node_list);
                    param_flag = false;
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
            string name = dynamic_cast<NodeTerminal*>(next_node->children[1])->get_name();
            if (name == "func" || name == "prog" || name == "lambda" || name == "while"){
                int idx = 3 + (name == "func");
                pair <int,int> interval = {next_node->children[idx]->get_interval().first,
                                           next_node->children[next_node->children.size() - 2]->get_interval().second};
                NodeBody* newNode = new NodeBody(next_node->get_bracket_info(), next_node->get_tokenized_code(), interval);
                for (int i = idx; i < next_node->children.size()-1; i++){
                    newNode->children.push_back(next_node->children[i]);
                }
                vector<Node*> _children;
                for (int i = 0; i < idx; i++)
                    _children.push_back(next_node->children[i]);
                _children.push_back(newNode);
                _children.push_back(next_node->children.back());
                next_node->children = _children;
            }
            if (!nodeSF->typecheck()){
                error = 1;
                error_messages.push_back("Error: Wrong usage of a special form at line " + 
                    to_string(nodeSF->get_tokenized_code()[nodeSF->get_interval().first + 1].line));
            }
        }
        if (dynamic_cast<ProgSF*> (nodeSF))
        {
            prog_count++;
            prog_params = (nodeSF->children[2]->children.size()) - 2;
        }
        third_traversal(next_node);
    }
}

void Semantixer::add_to_body_table(string atom, Node* value, int line){
    /*if (body_table[atom]){
        error = 1;
        error_messages.push_back("Error: Redefinition of an atom/function at line " + 
            to_string(line));
    }*/
    body_table[atom] = value;
}

void Semantixer::add_params(NodeParams* params){
    for(int i = 1; i < params->children.size() -1 ; i++){
        Node* node = params->children[i];
        string atom = node->get_tokenized_code()[node->get_interval().first].content;
        add_to_body_table(atom, new Node(), node->get_tokenized_code()[node->get_interval().first].line);
    }
}

void Semantixer::remove_local_context(NodeParams* params){
    for(int i = 1; i < params->children.size() -1 ; i++){
        Node* node = params->children[i];
        string atom = node->get_tokenized_code()[node->get_interval().first].content;
        body_table.erase(atom); 
    }
}

void Semantixer::forth_traversal(Node *node){
    if (dynamic_cast<SetqSF*>(node)){
        string atom = node->children[2]->get_tokenized_code()[node->get_interval().first + 2].content;
        Node* value = node->children[3];
        add_to_body_table(atom, value, node->get_tokenized_code()[node->get_interval().first + 1].line);
        node->body_table = body_table;
        node->param_table = param_table;
        forth_traversal(value);
    }
    else if (dynamic_cast<FuncSF*>(node)){
        string atom = node->children[2]->get_tokenized_code()[node->get_interval().first + 2].content;
        NodeParams* params = dynamic_cast<NodeParams*>(node->children[3]);
        Node* value = node->children[4];
        add_to_body_table(atom, value, node->get_tokenized_code()[node->get_interval().first + 1].line);
        param_table[atom] = params;
        node->body_table = body_table;
        node->param_table = param_table;    
        add_params(params);
        forth_traversal(value);
        remove_local_context(params);
    }
    else if (dynamic_cast<LambdaSF*>(node)){
        NodeParams* params = dynamic_cast<NodeParams*>(node->children[2]);
        Node* value = node->children[3];
        node->body_table = body_table;
        node->param_table = param_table;    
        add_params(params);
        forth_traversal(value);
        remove_local_context(params);
    }
    else if (dynamic_cast<ProgSF*>(node)){
        NodeParams* params = dynamic_cast<NodeParams*>(node->children[2]);
        Node* value = node->children[3];
        node->body_table = body_table;
        node->param_table = param_table;    
        add_params(params);
        forth_traversal(value);
        remove_local_context(params);
    }
    else if (dynamic_cast<QuoteSF*>(node)){
        node->body_table = body_table;
        node->param_table = param_table; 
        if (dynamic_cast<NodeList*> (node->children[2])){
            for (auto &next_node: node->children[2]->children){
                forth_traversal(next_node);
            }
        }
        else
            forth_traversal(node->children[2]);
    }
    else{
        node->body_table = body_table;
        node->param_table = param_table; 
        for(auto &next_node: node->children){
            forth_traversal(next_node);
        }
    }
    if (node->type == atom){
        string atom = node->get_tokenized_code()[node->get_interval().first].content;
        if (!node->body_table[atom]){
            error = 1;
            error_messages.push_back("Error: Reference to an undefined atom \'" + atom+ "\' in line " + 
                to_string(node->get_tokenized_code()[node->get_interval().first].line));
        }
    }
    else if (node->type == List){
        if (node->children.size() < 3){
            error = 1;
            error_messages.push_back("Error: Invalid list in line " + 
                to_string(node->get_tokenized_code()[node->get_interval().first].line));
            return;
        }
        string atom = node->get_tokenized_code()[node->children[1]->get_interval().first].content;
        if (!node->body_table[atom]){
            error = 1;
            error_messages.push_back("Error: Reference to an undefined function \'" + atom+ "\' in line " + 
                to_string(node->get_tokenized_code()[node->get_interval().first].line));
        }
        else if (!node->param_table[atom]){
            return;
            error = 1;
            error_messages.push_back("Error: atom \'" + atom + "\' is not a function in line " + 
                to_string(node->get_tokenized_code()[node->get_interval().first].line));
        }
        else if (node->param_table[atom]->children.size() != node->children.size() -1){
            error = 1;
            error_messages.push_back("Error: Unmatching number of arguments for function \'" + atom + "\' in line " + 
                to_string(node->get_tokenized_code()[node->get_interval().first].line));
        }
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

void Semantixer::print_errors(){
    cout << "Semantic error(s):\n";
    for (int i = 0; i < error_messages.size(); i++){
        cout << error_messages[i] << '\n';
    }
}