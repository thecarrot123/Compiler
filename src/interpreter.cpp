#include <interpreter.hpp>
#include <arithmetic_funs.hpp>
#include <logical_funs.hpp>
#include <predicate_funs.hpp>
#include <comparison_funs.hpp>
#include <list_funs.hpp>
#include <iostream>
#include <variant>

void Interpreter::interpret(){
    auto param_list = dynamic_cast<NodeParams*>(root->children.back()->children[2]);
    for (int i=1;i<param_list->children.size()-1;i++) {
        auto param = dynamic_cast<NodeTerminal*>(param_list->children[i]);
        auto param_quote = dynamic_cast<QuoteSF*>(param_root->children[i-1]);
        if(param_quote)
            context[param->get_name()] = new QuoteSF(*param_quote);
        else {
            auto param_value = dynamic_cast<NodeTerminal*>(param_root->children[i-1]->children[0]);
            context[param->get_name()] = new NodeTerminal(*param_value);
        }
    }
    root = root->children.back();
    Node* node = reduce(root);
    cout <<"done interpreting\n";
    root = node;
    print_code();
}

void Interpreter::print_error(string error_message, int error_number){
    cout <<error_message<<endl;
    exit(error_number);
}

bool Interpreter::ispredefined(Node *node){
    if (!dynamic_cast<NodeTerminal*>(node))
        return false;
    string name = dynamic_cast<NodeTerminal*>(node)->get_name();
    if (name == "plus" || name == "minus" || name == "times" || name == "divide" || name == "head" 
        || name == "tail" || name == "cons" || name == "equal" || name == "nonequal" || name == "less"
        || name == "lesseq" || name == "greater" || name == "greatereq" || name == "isint" || name == "isreal"
        || name == "isbool" || name == "isnull" || name == "isatom" || name == "islist" || name == "and"
        || name == "or" || name == "xor" || name == "not" || name == "isempty" || name == "eval")
        return true;
    return false;
}

Node* Interpreter::expand(Node* node){
    string name = dynamic_cast<NodeTerminal*>(node)->get_name();
    node = new Node(*context[name]);
    return node;
}

Node* Interpreter::reduce(Node *node) {
    if (dynamic_cast<ProgSF*>(node))
    {
        node = reduce(node->children[3]);
    }
    else if (node->type == Body){
        int return_index = node->children.size() - 1;
        for (int i = 0 ; i < node->children.size(); i++){
            node->children[i] = reduce(node->children[i]);
            if (return_flag)
            {
                return_flag = false;
                return_index = i;
                break;
            }
            if (break_flag)
                break;
        }
        node = node->children[return_index];
    }
    else if (node->type == SpecialForm){
        string name = dynamic_cast<NodeTerminal*>(node->children[1])->get_name();
        if (name == "quote"){
            return node;
        }
        else if (name == "setq"){
            node->children[3] = reduce(node->children[3]);
            string name = dynamic_cast<NodeTerminal*>(node->children[2])->get_name();
            if (dynamic_cast<NodeTerminal*>(node->children[3]))
                context[name] = new NodeTerminal (*dynamic_cast<NodeTerminal*>(node->children[3]));
            else if (dynamic_cast<QuoteSF*>(node->children[3]))
                context[name] = new QuoteSF (*dynamic_cast<QuoteSF*>(node->children[3]));
            else
                print_error("Invalid value returned from setq body!", 11);
            node = new NodeTerminal(
                node->get_bracket_info(),
                node->get_tokenized_code(),
                node->get_interval(),
                null,
                nullptr);
        }
        else if (name == "lambda"){
            if (!lambda_flag){
                print_error("Inappropriate use of a lambda function.", 16);
            }
            lambda_flag = false;
            param_context[lambda_param] = new Node(*(node->children[2]));
            context[lambda_param] = new Node(*(node->children[3]));
        }
        else if (name == "func"){
            print_error("Nested function is not supported!", 10);
        }
        else if (name == "cond"){
            node->children[2] = reduce(node->children[2]);
            if (node->children[2]->type != boolean)
                print_error("Condition statement isn't a boolean!", 11);
            if (get<bool>(dynamic_cast<NodeTerminal*>(node->children[2])->value) == true){
                node = reduce(node->children[3]);
            }
            else if (node->children.size() == 6){
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
        else if (name == "while"){
            Node* condition = new Node(*node->children[2]);
            Node* body = new Node(*node->children[3]);

            while (true){
                if (break_flag){
                    break_flag = false;
                    node = new NodeTerminal(
                        node->get_bracket_info(),
                        node->get_tokenized_code(),
                        node->get_interval(),
                        null,
                        nullptr);
                    break;
                }
                condition = reduce(condition);
                if (condition->type != boolean)
                    print_error("Error: Condition statement isn't boolean!", 13);
                NodeTerminal* _node = dynamic_cast<NodeTerminal*>(condition);
                if (get<bool>(_node->value)){
                    condition = new Node(*node->children[2]);
                    body = reduce(body);
                    body = new Node(*(node->children[3]));
                }
                else{
                    node = new NodeTerminal(
                        node->get_bracket_info(),
                        node->get_tokenized_code(),
                        node->get_interval(),
                        null,
                        nullptr);
                    break;
                }
            }    
        }
        else if (name == "break"){
            break_flag = true;
            node = new NodeTerminal(
                node->get_bracket_info(),
                node->get_tokenized_code(),
                node->get_interval(),
                null,
                nullptr);
        }
        else if (name == "return"){
            node = reduce(node->children[2]);
            return_flag = true;
        }
    }
    else if (node->type == List){
        for (int i = node->children.size()-2 ; i > 1 ;i--){
            if (!dynamic_cast<LambdaSF*>(node->children[i]))
                node->children[i] = reduce(node->children[i]);
        }
        if (ispredefined(node->children[1])){
            string name = dynamic_cast<NodeTerminal*>(node->children[1])->get_name();
            NodeList *params = new NodeList(*(node));
            params->children.erase(params->children.begin() + 1);
            if (name == "plus"){
                PlusFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "minus"){
                MinusFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "times"){
                TimesFun x(params, node->get_tokenized_code());
                node = x.run();
            } 
            else if (name == "divide"){
                DivideFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "head"){
                HeadFun x(params, node->get_tokenized_code());
                node = x.run();
            } 
            else if (name == "tail"){
                TailFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "cons"){
                ConsFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "equal"){
                EqualFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "nonequal"){
                NonequalFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "less"){
                LessFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "lesseq"){
                LesseqFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "greater"){
                GreaterFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "greatereq"){
                GreatereqFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "isint"){
                IsIntFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "isreal"){
                IsRealFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "isbool"){
                IsBoolFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "isnull"){
                IsNullFun x(params, node->get_tokenized_code());
                node = x.run();
            } 
            else if (name == "isatom"){
                IsAtomFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "islist"){
                IsListFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "isempty"){
                IsEmptyFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "and"){
                AndFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "or"){
                OrFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "xor"){
                XorFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "not"){
                NotFun x(params, node->get_tokenized_code());
                node = x.run();
            }
            else if (name == "eval"){
                EvalFun x(params, node->get_tokenized_code());
                node = x.run();
                node = reduce(node);
            }
        }
        else if (node->children[1]->type == atom){
            string name = dynamic_cast<NodeTerminal*>(node->children[1])->get_name();
            node->children[1] = expand(node->children[1]);
            Node* params = param_context[name];
            map <string, Node*> _context = context;
            map <string, Node*> _param_context = param_context;
            for (int i = 2; i < node->children.size() -1 ; i++){
                string param_name = dynamic_cast<NodeTerminal*>(params->children[i-1])->get_name();
                if ((node->children[i])->isTerminal())
                {
                    string temp = dynamic_cast<NodeTerminal*>(node->children[i])->get_name();
                    if (param_context[temp])
                    {
                        param_context[param_name] = new Node (*param_context[temp]);
                        context[param_name] = new Node (*context[temp]);
                    }
                    else
                        context[param_name] = new NodeTerminal(*dynamic_cast<NodeTerminal*>(node->children[i]));
                }
                else if (dynamic_cast<NodeTerminal*>(node->children[i]->children[1])->get_name() == "quote")
                {
                    context[param_name] = new Node(*(node->children[i]));
                }
                else{
                    lambda_flag = true;
                    lambda_param = param_name;
                    node->children[i] = reduce(node->children[i]);
                }
            }
            node = reduce(node->children[1]);
            context = _context;
            param_context = _param_context;
        }
        else{
            node->children[1] = reduce(node->children[1]);
        }
    }
    else if (node->type == Literal){
        node = reduce(node->children[0]);
    }
    else if (node->type == atom){
        string name = dynamic_cast<NodeTerminal*>(node)->get_name();
        if (!context[name]){
            print_error("Unresolved variable", 12);
        }
        if (!param_context[name])
        {
            node = context[name];
        }
    }
    else if (node->isTerminal()){
        return node;
    }
    else{
        print_error("Unknown error.", 69);
    }
    return node;
}

void Interpreter::print_code(Node *node){
    if (node->isTerminal()){
        NodeTerminal* _node = dynamic_cast<NodeTerminal*>(node);
        if (node->type == boolean){
            if (get<bool>(_node->value))
                cout<< "true ";
            else
                cout<< "false ";
        }
        else if (node->type == integer){
            cout<< to_string(get<int>(_node->value)) << " ";
        }
        else if (node->type == real){
            cout<< to_string(get<double>(_node->value)) << " ";
        }
        else if (node->type == null){
            cout<< "null ";
        }
        else
            cout<< _node->get_name() << " ";
        return;
    }
    if(node->children.size() > 2 && dynamic_cast<NodeTerminal*>(node->children[1]) 
        && dynamic_cast<NodeTerminal*>(node->children[1])->get_name() == "quote") {
        cout<<"\'";
        print_code(node->children[2]);
    }
    else {
        for (int i = 0; i < node->children.size();i ++){
            print_code(node->children[i]);
        }
    }
}

void Interpreter::print_code() {
    print_code(root);
    cout<<endl;
}

void Interpreter::print(ostream& fout, Node* node){
    fout << node->get_index() <<"[label=\""<< node->get_type() <<"\"]\n";
    for (int i = 0; i < node->children.size(); i++){
        Node* next_node = node->children[i];
        fout << node->get_index() <<" -- " <<next_node->get_index()<<"\n";
        print(fout, next_node);
    }
}


void Interpreter::print(string filename) {
    filebuf file;
    file.open(filename, ios::out);
    ostream fout(&file);
    fout << "graph {\n";
    print(fout, root);
    fout<<'}';
    file.close();
}