#ifndef TOKEN_HEADER
#define TOKEN_HEADER
#include <fstream>

using namespace std;

class Token{
public:
	string type;
	string content;

    operator string() const {
        return type + " " + content + "\n";
    }

	friend ostream& operator<<(ostream& os, const Token& token) {
		return os << token.type << ' ' << token.content;
	}
};

#endif