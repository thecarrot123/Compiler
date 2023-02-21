#include <fstream>

using namespace std;

class lexer {
private:
    ifstream fin;
    int keywords_number = 9;
    string keywords[9] = {"quote", "setq", "func", "lambda", "prog", "cond", "while", "return", "break"};

    virtual bool is_null()=0;
    virtual bool is_bracket()=0;
    virtual bool is_boolean()=0;
    virtual bool is_integer()=0;
    virtual bool is_real()=0;
    virtual bool is_literal()=0;
    virtual bool is_keyword()=0;
    virtual bool is_atom()=0;

public:
    lexer (string filename) {
        fin.open(filename);
    }
    virtual string parse_code()=0;
};