#ifndef TOKEN_HEADER
#define TOKEN_HEADER
#include <fstream>

using namespace std;

class Token{
public:
	string name;
	string content;

    operator string() const {
        return name + " " + content + "\n";
    }

	friend ostream& operator<<(ostream& os, const Token& tk) {
		return os << tk.name << ' ' << tk.content;
	}
};

#endif