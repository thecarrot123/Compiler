Node* reduce(Node* node){ -> NodeTerminal or NodeList

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

}

return reduce(root.children[n-2])
print_code();