#include <fstream>

using namespace std;

class token{
public:
	string name;
	string content;

	friend ostream& operator<<(ostream& os, const token& tk) {
		return os << tk.name << ' ' << tk.content;
	}
};