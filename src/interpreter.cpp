#include <interpreter.hpp>
#include <iostream>
#include <variant>

void Interpreter::print_error(string error_message, int error_number){
    cout <<error_message<<endl;
    exit(error_number);
}

Node* Interpreter::reduce(Node *node){
    if (dynamic_cast<NodeSpecialForm*>(node)){
        if (dynamic_cast<QuoteSF*>(node)){
            return node;
        }
        else if (dynamic_cast<SetqSF*>(node)){
            node = new NodeTerminal(
                node->get_bracket_info(),
                node->get_tokenized_code(),
                node->get_interval(),
                null,
                nullptr);
        }
        else if (dynamic_cast<FuncSF*>(node) || dynamic_cast<LambdaSF*>(node)){
            print_error("Nested function is not supported!", 10);
        }
        else if (dynamic_cast<CondSF*>(node)){
            node->children[2] = reduce(node->children[2]);
            if (node->children[2]->type != boolean)
                print_error("Condition statement isn't a boolean!", 11);
            if (get<bool>(dynamic_cast<NodeTerminal*>(node->children[2])->value) == true){
                node = reduce(node->children[3]);
            }
            else if (node->children.size() == 5){
                node = reduce(node->children[4]);
            }
            else{
                node = new NodeTerminal(
                    node->get_bracket_info(),
                    node->get_tokenized_code(),
                    node->get_interval(),
                    null,
                    nullptr);
            }
        }
        else if (dynamic_cast<WhileSF*>(node) || dynamic_cast<BreakSF*>(node)){
            return new NodeTerminal(
                node->get_bracket_info(),
                node->get_tokenized_code(),
                node->get_interval(),
                null,
                nullptr);
        }
        else if (dynamic_cast<ReturnSF*>(node)){
            node = reduce(node->children[2]);
        }
        return node;
    }
}

if (node == SF){
        if (node == quote){
            return node
        }
        else if (node == setq){
            return NodeTerminal(NULL);
        }
        else if (node == func || node == lambda){
            print_error("Nested function is not supported!", 10);
        }
        else if (node == cond){
            node.children[2] = reduce(node.children[2])
            if (node.children[2] == true){
                node = reduce(node.children[3]);
            }
            else if (node.children[2] == false){
                if (node.children.size() == 5){
                    node = reduce(node.children[4]);
                }
                else
                    node = new NodeTerminal(NULL);
            }
            else{
                print_error("Condition statement isn't a boolean!", 11);
            }
            return node;
        }
        else if (node == while){
            return null;
        }
        else if (node == return){
            node = reduce(node->chidlren[2]);
            return node;
        }
    }
    else if (node == list){
        for (int i = children.size()-2 ; i > 0 ;i--){
            children[i] = reduce(children[i])

        }
        if (predefined(children[1])){
            node = ...
        }
        else if (function(children[1])){
            children[1] = expand(children[1])
            //edit context based on children [2] -> [n-2]
            node = reduce(children[1])
            //reedit context
        }
        return node;
    }
    else if (node == atom){
        return new NodeTerminal()
    }
    else if (node == literal){
        return children[0];
    }
