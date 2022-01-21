#include <iostream>
#include <list>
#include <deque>
#include <set>
#include <string>

using namespace std;

struct Result
{
	string result;
	int times;
};

struct Card
{
	int value;
	Card(int value) : value(value) {}
};

struct Pile
{
	deque<Card> pile;
	void add(Card card)
	{
		pile.push_back(card);
	}
	bool empty()
	{
		return pile.empty();
	}
	bool PickUp(deque<Card> &deck)
	{
		if (pile.size() < 3) return false;
		Card first = pile[0], second = pile[1];
		Card ThirdLast = pile[pile.size() - 3], SecondLast = pile[pile.size() - 2], last = pile[pile.size() - 1];
		int comb1 = first.value + second.value + last.value;
		int comb2 = first.value + SecondLast.value + last.value;
		int comb3 = ThirdLast.value + SecondLast.value + last.value;
		if (comb1 == 10 || comb1 == 20 || comb1 == 30) {
			deck.push_back(first), pile.pop_front();
			deck.push_back(second), pile.pop_front();
			deck.push_back(last), pile.pop_back();
			return true;
		}
		if (comb2 == 10 || comb2 == 20 || comb2 == 30) {
			deck.push_back(first), pile.pop_front();
			deck.push_back(SecondLast);
			deck.push_back(last);
			pile.pop_back(), pile.pop_back();
			return true;
		}
		if (comb3 == 10 || comb3 == 20 || comb3 == 30) {
			deck.push_back(ThirdLast);
			deck.push_back(SecondLast);
			deck.push_back(last);
			pile.pop_back(), pile.pop_back(), pile.pop_back();
			return true;
		}
		return false;
	}
};

string CurrentState(const deque<Card> &deck, const list<Pile> &piles)
{
	string state;
	for (const Card &card : deck)
	{
		state.push_back(static_cast<char>((card.value - 1) + '0'));
	}
	state.push_back('|');
	for (const Pile &pile : piles)
	{
		for (const Card &card : pile.pile)
		{
			state.push_back(static_cast<char>((card.value - 1) + '0'));
		}
		state.push_back('|');
	}
	return state;
}

Result play(deque<Card> &deck)
{
	set<string> states;
	list<Pile> piles(7);
	int times = 7;
	for (Pile &pile : piles)
	{
		pile.add(deck.front());
		deck.pop_front();
	}
	while (1) {
		for (auto PileIter = piles.begin(); PileIter != piles.end();)
		{
			if (deck.empty()) return{ "Loss", times };
			string state = CurrentState(deck, piles);
			if (states.find(state) != states.end()) return{ "Draw", times };
			else states.insert(state);
			PileIter->add(deck.front());
			deck.pop_front();
			times++;
			while (PileIter->PickUp(deck));
			if (PileIter->empty()) {
				PileIter = piles.erase(PileIter);
				if (piles.empty()) return{ "Win ", times };
			}
			else PileIter++;
		}
	}
}

int main()
{
	int value;
	while (cin >> value) {
		if (value == 0) break;
		deque<Card> deck(1, Card(value));
		for (size_t i = 0; i < 51; i++)
		{
			cin >> value;
			deck.push_back(value);
		}
		Result result = play(deck);
		cout << result.result << ": " << result.times << endl;
	}
	return 0;
}
/*
2 6 5 10 10 4 10 10 10 4 5 10 4 5 10 9 7 6 1 7 6 9 5 3 10 10 4 10 9 2 1
10 1 10 10 10 3 10 9 8 10 8 7 1 2 8 6 7 3 3 8 2
4 3 2 10 8 10 6 8 9 5 8 10 5 3 5 4 6 9 9 1 7 6 3 5 10 10 8 10 9 10 10 7
2 6 10 10 4 10 1 3 10 1 1 10 2 2 10 4 10 7 7 10
10 5 4 3 5 7 10 8 2 3 9 10 8 4 5 1 7 6 7 2 6 9 10 2 3 10 3 4 4 9 10 1 1
10 5 10 10 1 8 10 7 8 10 6 10 10 10 9 6 2 10 10
0
*/
