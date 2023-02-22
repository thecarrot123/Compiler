#include <iostream>
#include "lexer.h"
#include "token.h"

using namespace std;

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

bool Lexer::is_null(const string &s) {
	return (s == "null");
}

bool Lexer::is_bracket(char c) {
    return (c == '(' || c == ')' || c == '[' || c == ']');
}

bool Lexer::is_boolean(const string &s) {
	return (s == "true" || s == "false");
}

bool Lexer::is_integer(const string &s) {
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

bool Lexer::is_real(const string &s) {
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

bool Lexer::is_literal(const string &s) {
	return ( is_boolean(s) || is_integer(s) || is_real(s) || is_null(s) );
}

bool Lexer::is_keyword(const string &s){
    for (int i=0;i<keywords_number;i++)
    {
        if (keywords[i] == s)
            return true;
    }
    return false;
}

bool Lexer::is_atom(const string &s) {
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

string Lexer::token_type(const string &s) {
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
	if ( is_bracket(s[0]) )
		return bracket_name(s);
	return "ERR";
}

string Lexer::next_token_content() {
    while (ind < code.size() && (code[ind] == ' ' || code[ind] == '\n' || code[ind] == '\t'))
        ind++;
    if (ind >= code.size())
        return "";
    string ret = "";
    while (code[ind] != ' ' && code[ind] != '\n' && code[ind] != '\t') {
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

Token Lexer::next_token() {
	string content = next_token_content();
	Token tok = {token_type(content), content};
	return tok;
}

string Lexer::scan_code() {
    string input;
    while (getline(fin, input)) {
        code+= input + '\n';
    }
    string tokenized_code;
    Token token;
    token = next_token();
    while (token.content != "") {
        tokenized_code += token;
        token = next_token();
    }
    return tokenized_code;
}

/**
TODO: fix errors in sample.F
*/