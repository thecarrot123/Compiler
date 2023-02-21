#include <iostream>
#include "token.h"
#include "lexer.h"

using namespace std;
string code;
int ind;
string KEYWORDS[9] = {"quote", "setq", "func", "lambda", "prog", "cond", "while", "return", "break"};

string bracket_name(char c) {
    if (c == '(')
        return "LPAR";
    if (c == ')')
        return "RPAR";
    if (c == '[')
        return "LBRAC";
    if (c == ']')
        return "RBRAC";
	return "Error finding bracket name";
}

string bracket_name(const string &s) {
	char c = s[0];
    if (c == '(')
        return "LPAR";
    if (c == ')')
        return "RPAR";
    if (c == '[')
        return "LBRAC";
    if (c == ']')
        return "RBRAC";
	return "Error finding bracket name";
}

bool is_null(const string &s) {
	return (s == "null");
}

bool is_bracket(char c) {
    return (c == '(' || c == ')' || c == '[' || c == ']');
}

bool is_bracket(const string &s) {
	char c = s[0];
    return (c == '(' || c == ')' || c == '[' || c == ']');
}

bool is_boolean(const string &s) {
	return (s == "true" || s == "false");
}

bool is_integer(const string &s) {
	bool _signed = false;
	if ( s[0] == '-' || s[0] == '+' )
		_signed = true;
	for (int i=_signed;i<(int)s.size();i++) {
		if( !isdigit(s[i]) ) {
			return false;
		}
	}
	return true;
}

bool is_real(const string &s) {
	bool has_dot = false;
	bool _signed = false;
	if ( s[0] == '-' || s[0] == '+')
		_signed = true;
	for (int i=_signed;i<(int)s.size();i++) {
		if ( has_dot == false && s[i] == '.' ) {
			has_dot = true;
		}
		else if ( !isdigit(s[i]) ) {
			return false;
		}
	}
	return has_dot;
}

bool is_literal(const string &s) {
	return ( is_boolean(s) || is_integer(s) || is_real(s) || is_null(s) );
}

bool is_keyword(const string &s){
    for (int i=0;i<9;i++)
    {
        if (KEYWORDS[i] == s)
            return true;
    }
    return false;
}

bool is_atom(const string &s) {
	if ( is_boolean(s) || is_null(s) || is_keyword(s) )
		return false;

	if ( isalpha(s[0]) ) {
		bool error = false;
		for (int i=1;i<(int)s.size();i++) {
			if( !isalpha(s[i]) && !isdigit(s[i]) ) {
				error = true;
				break;
			}
		}
		if ( !error ) {
			return true;
		}
	}
	return false;
}

string token_name(const string &s) {
	if ( is_boolean(s) )
		return "BOOL";
	if ( is_integer(s) )
		return "INT";
	if ( is_real(s) )
		return "REAL";
	if ( is_null(s) )
		return "NULL";
    if ( is_keyword(s) )
        return "KEYWORD";
	if ( is_atom(s) )
		return "ATOM";
	if ( is_bracket(s) )
		return bracket_name(s);
	return "ERR";
}

string next_token_content() {
    while (ind < code.size() && (code[ind] == ' ' || code[ind] == '\n'))
        ind++;
    if (ind >= code.size())
        return "";
    string ret = "";
    while (code[ind] != ' ' && code[ind] != '\n') {
        if (is_bracket(code[ind])) {
            if (ret != "")
                return ret;
            ret = code[ind];
            ind ++;
            return ret;
        }
        if(code[ind] == '/' && code[ind+1] == '/') {
            while (code[ind] != '\n' && code[ind] != EOF)
                ind++;
            if (ret == "")
                return next_token_content();
            break;
        }
        ret += code[ind];
        ind++;
    }
    ind++;
    return ret;
}

token next_token() {
	string content = next_token_content();
	token tok = {token_name(content), content};
	return tok;
}

int main() {
    freopen("sample.F", "r", stdin);
    string input;
    while (getline(cin, input)) {
        code+= input + '\n';
    }
    token pp;
    pp = next_token();
    while (pp.content != "") {
        cout << pp << endl;
        pp = next_token();
    }
    return 0;
}
/**
TODO:
3) what to do in case of error?
4) improve code
5) print all errors together
*/
/*
quote setq func lambda prog cond while return break
*/
