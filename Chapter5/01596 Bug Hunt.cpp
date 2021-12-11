#include <iostream>
#include <climits>
#include <map>
#include <string>

using namespace std;

struct Array
{
	char name;
	int size;
	map<int, int> arr;
	Array(char ch, int size) : name(ch), size(size) {}
};

int ParseNumber(const string &number)
{
	int size = 0;
	for (size_t i = 0; i < number.size(); i++)
	{
		size *= 10;
		size += number[i] - '0';
	}
	return size;
}

bool ParseExpr(const string &expr, map<char, Array> &declarations, bool RW, int &value)
{
	if (isdigit(expr[0])) {
		value = ParseNumber(expr);
		return true;
	}
	int index;
	if (declarations.find(expr[0]) == declarations.end()) return false;
	Array &arr = declarations.at(expr[0]);
	if (isdigit(expr[2])) {
		index = ParseNumber(expr.substr(2, expr.size() - 3));
	}
	else {
		if (!ParseExpr(expr.substr(2, expr.size() - 3), declarations, true, index)) {
			return false;
		}
	}
	if (index >= arr.size) return false;
	if (RW) {
		if (arr.arr.find(index) == arr.arr.end()) return false;
		else value = arr.arr.at(index);
		return true;
	}
	else {
		arr.arr[index] = value;
		return true;
	}
}

bool ParseStatement(const string &statement, map<char, Array> &declarations)
{
	size_t equal = statement.find("=");
	int value;
	if (equal == string::npos) {
		declarations.insert(make_pair(statement[0], Array(statement[0], ParseNumber(statement.substr(2, statement.size() - 3)))));
		return true;
	}
	else {
		return ParseExpr(statement.substr(equal + 1), declarations, true, value)
			&& ParseExpr(statement.substr(0, equal), declarations, false, value);
	}
}

int main()
{
	string input;
	while (1) {
		size_t CurrLine = 1, ErrLine = 0;
		map<char, Array> arrays;
		cin >> input;
		if (input[0] == '.') break;
		if (!ParseStatement(input, arrays)) {
			ErrLine = CurrLine;
		}
		while (cin >> input) {
			CurrLine++;
			if (input[0] == '.') break;
			if (ErrLine == 0 && !ParseStatement(input, arrays)) {
				ErrLine = CurrLine;
			}
		}
		cout << ErrLine << endl;
	}
	return 0;
}
/*
a[3]
a[0]=a[1]
.
x[1]
x[0]=x[0]
.
a[0]
a[0]=1
.
b[2]
b[0]=2
b[1]=b[b[0]]
b[0]=b[1]
.
g[2]
G[10]
g[0]=0
g[1]=G[0]
.
a[2147483647]
a[0]=1
B[2]
B[a[0]]=2
a[B[a[0]]]=3
a[2147483646]=a[2]
.
.
*/
