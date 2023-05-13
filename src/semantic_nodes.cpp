#include "semantic_nodes.hpp"

Node* QuoteSF::clone(){
    return new QuoteSF(*this);
}

Node* SetqSF::clone(){
    return new SetqSF(*this);
}

Node* FuncSF::clone(){
    return new FuncSF(*this);
}

Node* LambdaSF::clone(){
    return new LambdaSF(*this);
}

Node* ProgSF::clone(){
    return new ProgSF(*this);
}

Node* CondSF::clone(){
    return new CondSF(*this);
}

Node* WhileSF::clone(){
    return new WhileSF(*this);
}

Node* BreakSF::clone(){
    return new BreakSF(*this);
}

Node* NodeParams::clone(){
    return new NodeParams(*this);
}

Node* ReturnSF::clone(){
    return new ReturnSF(*this);
}

bool isAtom(Node* node){
    return (node->type == atom);
}

bool isElement(Node* node){
    return (dynamic_cast<NodeList*>(node) || dynamic_cast<NodeLiteral*>(node) || isAtom(node));
}

bool QuoteSF::typecheck(){
    if (children.size() != 4)
        return false;
    return isElement(children[2]);
}

bool SetqSF::typecheck(){
    if (children.size() != 5)
        return false;
    return (isAtom(children[2]) && isElement(children[3]));
}

bool FuncSF::typecheck(){
    if (children.size() != 6)
        return false;
    return (isAtom(children[2]) && dynamic_cast<NodeParams*>(children[3]) && dynamic_cast<NodeBody*>(children[4]));
}

bool LambdaSF::typecheck(){
    if (children.size() != 5)
        return false;
    return (dynamic_cast<NodeParams*>(children[2]) && dynamic_cast<NodeBody*>(children[3]));
}

bool ProgSF::typecheck(){
    if (children.size() != 5)
        return false;
    return (dynamic_cast<NodeParams*>(children[2]) && dynamic_cast<NodeBody*>(children[3]));
}

bool CondSF::typecheck(){
    if (children.size() < 5 || children.size() > 6)
        return false;
    return true;
}

bool WhileSF::typecheck(){
    if (children.size() != 5)
        return false;
    return (isElement(children[2]) && dynamic_cast<NodeBody*>(children[3]));
}

bool ReturnSF::typecheck(){
    if (children.size() != 4)
        return false;
    return (isElement(children[2]));
}

bool BreakSF::typecheck(){
    if (children.size() != 3)
        return false;
    return true;
}
