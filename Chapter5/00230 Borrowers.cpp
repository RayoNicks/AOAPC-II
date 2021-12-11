#include <iostream>
#include <set>
#include <string>

using namespace std;

struct Book
{
	string title;
	string author;
	Book(const string &title, const string &author)
		: title(title), author(author) {};
	bool operator<(const Book &book) const
	{
		if (author < book.author) return true;
		else if (author == book.author) return title < book.title;
		else return false;
	}
};

set<Book>::iterator SearchBookByTitle(set<Book> &shelf, const string &title)
{
	for (auto iter = shelf.begin(); iter != shelf.end(); iter++)
	{
		if (iter->title == title) {
			return iter;
		}
	}
	return shelf.end();
}

int main()
{
	string input;
	size_t pos;
	set<Book> shelf, borrowed, returned;
	while (getline(cin, input)) {
		if (input == "END") break;
		pos = input.find('"', 1);
		Book book(input.substr(0, pos + 1), input.substr(pos + 5));
		shelf.insert(book);
	}
	while (getline(cin, input)) {
		if (input == "END") break;
		pos = input.find(' ');
		string cmd(input.substr(0, pos)), title(input.substr(pos + 1));
		if (cmd[0] == 'B') {
			set<Book>::iterator iter = SearchBookByTitle(shelf, title);
			if (iter != shelf.end()) {
				borrowed.insert(*iter);
				shelf.erase(iter);
			}
		}
		else if (cmd[0] == 'R') {
			set<Book>::iterator iter = SearchBookByTitle(borrowed, title);
			if (iter != borrowed.end()) {
				returned.insert(*iter);
				borrowed.erase(iter);
			}
		}
		else if (cmd[0] == 'S') {
			for (const Book &book : returned)
			{
				cout << "Put " << book.title;
				auto iter = shelf.lower_bound(book);
				if (iter == shelf.begin()) {
					cout << " first" << endl;
				}
				else {
					cout << " after " << (--iter)->title << endl;
				}
				shelf.insert(book);
			}
			returned.clear();
			cout << "END" << endl;
		}
		else;
	}
	return 0;
}
/*
"The Canterbury Tales" by Chaucer, G.
"Algorithms" by Sedgewick, R.
"The C Programming Language" by Kernighan, B. and Ritchie, D.
END
BORROW "Algorithms"
BORROW "The C Programming Language"
RETURN "Algorithms"
RETURN "The C Programming Language"
SHELVE
END
*/
