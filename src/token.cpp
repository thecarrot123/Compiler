#include "token.hpp"
#include <string>

using namespace std;

const string Token::keywords[] = {"quote", "setq", "func", "lambda", "prog", "cond", "while", "return", "break"};
const int Token::keywords_num = 9;
const string Token::types[] = {"ERR","LPAR","RPAR","LBRAC",
    "RBRAC","BOOL","INT","REAL","NUL","KEYWORD","ATOM"};
const int Token::types_num = 11;

string bracket_name(char c) {
    if (c == '(')
        return "LPAR";
    if (c == ')')
        return "RPAR";
    if (c == '[')
        return "LBRAC";
    if (c == ']')
        return "RBRAC";
	return "ERR";
}

bool is_null(const string &s) {
	return (s == "null");
}

bool is_bracket(char c) {
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

bool is_keyword(const string &s) {
    for (int i=0;i<Token::keywords_num;i++)
    {
        if (Token::keywords[i] == s)
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

string Token::find_type_name(const string &s) {
	if ( is_boolean(s) )
		return "BOOL";
	if ( is_integer(s) )
		return "INT";
	if ( is_real(s) )
		return "REAL";
	if ( is_null(s) )
		return "NUL";
    if ( is_keyword(s) )
        return "KEYWORD";
	if ( is_atom(s) )
		return "ATOM";
	if ( is_bracket(s[0]) )
		return bracket_name(s[0]);
	return "ERR";
}

token_type Token::find_type(const string &s) {
    token_type type = find_type_in_types(s);
    if( type == 0 )
        return find_type_in_types(find_type_name(s));
    return type;
}

token_type Token::find_type_in_types(const string &type) {
	for (int i=0;i<types_num;i++) {
		if(type == types[i]) {
			return token_type(i);
		}
	}
	return token_type::ERR;
}