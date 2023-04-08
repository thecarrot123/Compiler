#include "semantic_nodes.hpp"

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
    return (isAtom(children[2]) && dynamic_cast<NodeParams*>(children[3]) && isElement(children[4]));
}

bool LambdaSF::typecheck(){
    if (children.size() != 5)
        return false;
    return (dynamic_cast<NodeParams*>(children[2]) && isElement(children[3]));
}

bool ProgSF::typecheck(){
    if (children.size() != 5)
        return false;
    return (dynamic_cast<NodeParams*>(children[2]) && isElement(children[3]));
}

bool CondSF::typecheck(){
    /// TODO: check more
}

bool WhileSF::typecheck(){
    if (children.size() != 5)
        return false;
    return (isElement(children[2]) && isElement(children[3]));
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
