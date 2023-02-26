#ifndef TOKEN_HEADER
#define TOKEN_HEADER
#include <fstream>
#include <sstream>

using namespace std;

enum token_type {
    ERR,
    LPAR,
    RPAR,
    LBRAC,
    RBRAC,
    BOOL,
    INT,
    REAL,
    NUL,
    KEYWORD,
    ATOM,
};

class Token{
private:
	token_type find_type_in_types(const string &type);
	string find_type_name(const string &s);
	
public:
	static const string keywords[];
    static const int keywords_num;
	static const int types_num;
	static const string types[];
	token_type type;
	string content;
	int line;

	Token(string content, int line) {
		this->type = find_type(content);
		this->content = content;
		this->line = line;
	}

	Token() {
		this->type = token_type::ERR;
		this->content = "";
		this->line = 0;
	}

	Token& operator=(const Token& token) {
		this->type = token.type;
		this->content = token.content;
		this->line = token.line;
		return *this;
	}
	
	string get_type() {
		return types[type];
	}

	void set_type() {
		if(type) {
			type = find_type(content);
		}
	}

    operator string() const {
        stringstream buffer;
		buffer << *this << endl;
		return buffer.str();
    }

	friend ostream& operator<<(ostream& os, const Token& token) {
		return os << types[token.type] << ' ' << token.content << " : " << token.line;
	}

	token_type find_type(const string &s);
	
};
#endif