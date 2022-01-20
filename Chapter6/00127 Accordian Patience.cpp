#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Card
{
	char suit;
	int rank;
	Card(char FaceValue, char suit) : suit(suit)
	{
		if (FaceValue == 'A') rank = 1;
		else if (FaceValue == 'T') rank = 10;
		else if (FaceValue == 'J') rank = 11;
		else if (FaceValue == 'Q') rank = 12;
		else if (FaceValue == 'K') rank = 13;
		else rank = FaceValue - '0';
	}
	bool match(const Card &card)
	{
		return suit == card.suit || rank == card.rank;
	}
};

struct Pile
{
	vector<Card> cards;
	void add(const Card &card)
	{
		cards.push_back(card);
	}
	bool match(const Pile &pile)
	{
		return cards.back().match(pile.cards.back());
	}
	void MoveTo(Pile &pile)
	{
		pile.add(cards.back());
		cards.pop_back();
	}
	bool empty()
	{
		return cards.empty();
	}
	size_t size()
	{
		return cards.size();
	}
};

void play(list<Pile> &piles)
{
	while (1) {
		list<Pile>::iterator curr, left, left3;
		size_t i = 1;
		bool moved = false;
		for (left = piles.begin(), curr = ++piles.begin(); i < 3 && i < piles.size(); i++, curr++, left++)
		{
			if (left->match(*curr)) {
				curr->MoveTo(*left);
				if (curr->empty()) piles.erase(curr);
				moved = true;
				break;
			}
		}
		if (moved) continue;
		for (left3 = piles.begin(); curr != piles.end(); curr++, left++, left3++)
		{
			if (left3->match(*curr)) {
				curr->MoveTo(*left3);
				if (curr->empty()) piles.erase(curr);
				moved = true;
				break;
			}
			if (left->match(*curr)) {
				curr->MoveTo(*left);
				if (curr->empty()) piles.erase(curr);
				moved = true;
				break;
			}
		}
		if (!moved) break;
	}
}

int main()
{
	string line;
	while (getline(cin, line)) {
		if (line == "#") break;
		list<Pile> piles;
		string str;
		do {
			stringstream ss(line);
			while (ss >> str) {
				piles.push_back(Pile());
				piles.back().add(Card(str[0], str[1]));
			}
			if (piles.size() == 52) break;
		} while (getline(cin, line));
		play(piles);
		if (piles.size() != 1) cout << piles.size() << " piles remaining:";
		else cout << "1 pile remaining:";
		for (Pile &pile : piles)
		{
			cout << ' ' << pile.size();
		}
		cout << endl;
	}
	return 0;
}
/*
QD AD 8H 5S 3H 5H TC 4D JH KS 6H 8S JS AC AS 8D 2H QS TS 3S AH 4H TH TD 3C 6S
8C 7D 4C 4S 7S 9H 7C 5D 2S KD 2D QH JD 6D 9D JC 2C KH 3D QC 6C 9S KC 7H 9C 5C
AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D TD 9D JD QD KD
AH 2H 3H 4H 5H 6H 7H 8H 9H KH 6S QH TH AS 2S 3S 4S 5S JH 7S 8S 9S TS JS QS KS
#
*/
