#ifndef COMPARISON_FUNCTIONS_HEADER
#define COMPARISON_FUNCTIONS_HEADER
#include "semantic_nodes.hpp"
#include "predefined_funs.hpp"

class ComparisonFun : public PredefinedFun {
protected:
    NodeParams *create_params();

    void typecheck() override;
    
    double get_comparison_val(NodeTerminal *node);

public:

    ComparisonFun(PredefinedFunTypes name, NodeParams *params, vector <Token> &vec) : PredefinedFun(name,params,vec) {}
};

class EqualFun : public ComparisonFun{
public:
    EqualFun(vector <Token> &vec) : ComparisonFun(_equal,create_params(),vec) {}

    EqualFun(NodeParams *params, vector <Token> &vec) : ComparisonFun(_equal,params,vec) { }

    Node* run() override;
};

class NonequalFun : public ComparisonFun{
public:
    NonequalFun(vector <Token> &vec) : ComparisonFun(_nonequal,create_params(),vec) {}

    NonequalFun(NodeParams *params, vector <Token> &vec) : ComparisonFun(_nonequal,params,vec) { }

    Node* run() override;
};

class LessFun : public ComparisonFun{
public:
    LessFun(vector <Token> &vec) : ComparisonFun(_less,create_params(),vec) {}

    LessFun(NodeParams *params, vector <Token> &vec) : ComparisonFun(_less,params,vec) { }

    Node* run() override;
};

class LesseqFun : public ComparisonFun{
public:
    LesseqFun(vector <Token> &vec) : ComparisonFun(_lesseq,create_params(),vec) {}

    LesseqFun(NodeParams *params, vector <Token> &vec) : ComparisonFun(_lesseq,params,vec) { }

    Node* run() override;
};

class GreaterFun : public ComparisonFun{
public:
    GreaterFun(vector <Token> &vec) : ComparisonFun(_greater,create_params(),vec) {}

    GreaterFun(NodeParams *params, vector <Token> &vec) : ComparisonFun(_greater,params,vec) { }

    Node* run() override;
};

class GreatereqFun : public ComparisonFun{
public:
    GreatereqFun(vector <Token> &vec) : ComparisonFun(_greatereq,create_params(),vec) {}

    GreatereqFun(NodeParams *params, vector <Token> &vec) : ComparisonFun(_greatereq,params,vec) { }

    Node* run() override;
};

#endif