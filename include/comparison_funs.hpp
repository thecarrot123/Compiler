#ifndef COMPARISON_FUNCTIONS_HEADER
#define COMPARISON_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class ComparisonFun : public PredefinedFun {
protected:
    void typecheck() override;
    
    double get_comparison_val(NodeTerminal *node);

public:

    ComparisonFun(PredefinedFunTypes name, NodeList *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}
};

class EqualFun : public ComparisonFun{
public:
    EqualFun(NodeList *params, vector <Token> &vec) : ComparisonFun(_equal,params,vec) { }

    Node* run() override;
};

class NonequalFun : public ComparisonFun{
public:
    NonequalFun(NodeList *params, vector <Token> &vec) : ComparisonFun(_nonequal,params,vec) { }

    Node* run() override;
};

class LessFun : public ComparisonFun{
public:
    LessFun(NodeList *params, vector <Token> &vec) : ComparisonFun(_less,params,vec) { }

    Node* run() override;
};

class LesseqFun : public ComparisonFun{
public:
    LesseqFun(NodeList *params, vector <Token> &vec) : ComparisonFun(_lesseq,params,vec) { }

    Node* run() override;
};

class GreaterFun : public ComparisonFun{
public:
    GreaterFun(NodeList *params, vector <Token> &vec) : ComparisonFun(_greater,params,vec) { }

    Node* run() override;
};

class GreatereqFun : public ComparisonFun{
public:
    GreatereqFun(NodeList *params, vector <Token> &vec) : ComparisonFun(_greatereq,params,vec) { }

    Node* run() override;
};

#endif