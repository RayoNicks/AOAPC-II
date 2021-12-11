#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define INDENT "     "

using namespace std;

struct User
{
	string name;
	string mta;
	User(const string &address)
	{
		size_t AtPos = address.find('@');
		name.assign(address.substr(0, AtPos));
		mta.assign(address.substr(AtPos + 1));
	}
	User(const string &name, const string mta) : name(name), mta(mta) {};
	bool operator<(const User &user) const
	{
		return name + mta < user.name + user.mta;
	}
	string address() const
	{
		return name + '@' + mta;
	}
};

void SendMsg(const set<User> &ExistedUsers, const User &sender, const vector<User> &receivers, const vector<string> &MsgLines)
{
	map<string, vector<User>> ToSend;
	set<User> sent;
	for (const User &user : receivers)
	{
		if (sent.insert(user).second) {
			ToSend[user.mta].push_back(user);
		}
	}
	for (const User &user : receivers)
	{
		vector<User> &SameMTAUsers = ToSend.at(user.mta);
		if (SameMTAUsers.empty()) continue;
		bool NeedSend = false;
		cout << "Connection between " << sender.mta << " and " << user.mta << '\n';
		cout << INDENT"HELO " << sender.mta << '\n';
		cout << INDENT"250\n";
		cout << INDENT"MAIL FROM:<" << sender.address() << ">\n";
		cout << INDENT"250\n";
		for (const User &receiver : SameMTAUsers)
		{
			cout << INDENT"RCPT TO:<" << receiver.address() << ">\n";
			if (ExistedUsers.find(receiver) == ExistedUsers.end()) {
				cout << INDENT"550\n";
				continue;
			}
			else {
				NeedSend = true;
				cout << INDENT"250\n";
			}
		}
		if (NeedSend) {
			cout << INDENT"DATA\n";
			cout << INDENT"354\n";
			for (const string &line : MsgLines)
			{
				cout << INDENT << line << '\n';
			}
			cout << INDENT".\n";
			cout << INDENT"250\n";
		}
		cout << INDENT"QUIT\n";
		cout << INDENT"221\n";
		SameMTAUsers.clear();
	}
}

int main()
{
	string input;
	set<User> ExistedUsers;
	while (getline(cin, input)) {
		if (input == "*") break;
		stringstream ss(input.substr(4));
		string mta, name;
		int n;
		ss >> mta >> n;
		for (int i = 0; i < n; i++)
		{
			ss >> name;
			ExistedUsers.insert(User(name, mta));
		}
	}
	while (1) {
		cin >> input;
		if (input == "*") break;
		User sender(input);
		vector<User> receivers;
		while (cin >> input) {
			if (input == "*") break;
			receivers.push_back(User(input));
		}
		cin.get();
		vector<string> MsgLines;
		while (getline(cin, input)) {
			if (input == "*") break;
			MsgLines.push_back(input);
		}
		SendMsg(ExistedUsers, sender, receivers, MsgLines);
	}
	return 0;
}
/*
MTA London 4 Fiona Paul Heather Nevil
MTA SanFrancisco 3 Mario Luigi Shariff
MTA Paris 3 Jacque Suzanne Maurice
MTA HongKong 3 Chen Jeng Hee
MTA MexicoCity 4 Conrado Estella Eva Raul
MTA Cairo 3 Hamdy Tarik Misa
*
Hamdy@Cairo Conrado@MexicoCity Shariff@SanFrancisco Lisa@MexicoCity
*
Congratulations on your efforts !!
--Hamdy
*
Fiona@London Chen@HongKong Natasha@Paris
*
Thanks for the report! --Fiona
*
*
*/
