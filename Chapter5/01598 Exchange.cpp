#include <iostream>
#include <algorithm>
#include <climits>
#include <list>
#include <map>
#include <string>
#include <vector>

#define MAX_ASK_PRICE 100000

using namespace std;

enum class OrderType
{
	BUY, SELL, CANCEL
};

struct Order
{
	OrderType type;
	int size, price;
	bool active;
};

struct OrderQueue
{
	int total;
	list<size_t> indexes;
	OrderQueue() : total(0) {};
	void append(int size, size_t index)
	{
		this->total += size;
		indexes.push_back(index);
	}
};

void ProcessBuy(vector<Order> &orders, map<int, OrderQueue> &BidPrices, map<int, OrderQueue> &AskPrices)
{
	Order &BuyOrder = orders.back();
	while (BuyOrder.size != 0 && BuyOrder.price >= AskPrices.begin()->first) {
		int AskPrice = AskPrices.begin()->first;
		OrderQueue &AskQueue = AskPrices.begin()->second;
		while (BuyOrder.size != 0 && !AskQueue.indexes.empty()) {
			Order &SellOrder = orders[AskQueue.indexes.front()];
			int TradeSize = min(BuyOrder.size, SellOrder.size);
			cout << "TRADE " << TradeSize << ' ' << AskPrice << endl;
			BuyOrder.size -= TradeSize;
			SellOrder.size -= TradeSize;
			AskQueue.total -= TradeSize;
			if (SellOrder.size == 0) {
				SellOrder.active = false;
				AskQueue.indexes.pop_front();
			}
		}
		if (AskQueue.indexes.empty()) {
			AskPrices.erase(AskPrices.begin());
		}
	}
	BuyOrder.active = BuyOrder.size != 0;
	if (BuyOrder.active) {
		BidPrices[BuyOrder.price].append(BuyOrder.size, orders.size() - 1);
	}
}

void ProcessSell(vector<Order> &orders, map<int, OrderQueue> &BidPrices, map<int, OrderQueue> &AskPrices)
{
	Order &SellOrder = orders.back();
	while (SellOrder.size != 0 && SellOrder.price <= BidPrices.rbegin()->first) {
		int BidPrice = BidPrices.rbegin()->first;
		OrderQueue &BidQueue = BidPrices.rbegin()->second;
		while (SellOrder.size != 0 && !BidQueue.indexes.empty()) {
			Order &BuyOrder = orders[BidQueue.indexes.front()];
			int TradeSize = min(SellOrder.size, BuyOrder.size);
			cout << "TRADE " << TradeSize << ' ' << BidPrice << endl;
			SellOrder.size -= TradeSize;
			BuyOrder.size -= TradeSize;
			BidQueue.total -= TradeSize;
			if (BuyOrder.size == 0) {
				BuyOrder.active = false;
				BidQueue.indexes.pop_front();
			}
		}
		if (BidQueue.indexes.empty()) {
			BidPrices.erase(BidPrices.rbegin()->first);
		}
	}
	SellOrder.active = SellOrder.size != 0;
	if (SellOrder.active) {
		AskPrices[SellOrder.price].append(SellOrder.size, orders.size() - 1);
	}
}

void ProcessCancel(vector<Order> &orders, map<int, OrderQueue> &BidPrices, map<int, OrderQueue> &AskPrices)
{
	Order &CanceledOrder = orders[orders.back().size - 1];
	if (!CanceledOrder.active) return;
	if (CanceledOrder.type == OrderType::BUY) {
		OrderQueue &BidQueue = BidPrices[CanceledOrder.price];
		BidQueue.total -= CanceledOrder.size;
		if (BidQueue.total == 0) {
			BidPrices.erase(CanceledOrder.price);
		}
		else {
			BidQueue.indexes.remove_if([&orders](const size_t idx)
			{
				return idx == orders.back().size - 1;
			});
		}
	}
	else {
		OrderQueue &AskQueue = AskPrices[CanceledOrder.price];
		AskQueue.total -= CanceledOrder.size;
		if (AskQueue.total == 0) {
			AskPrices.erase(CanceledOrder.price);
		}
		else {
			AskQueue.indexes.remove_if([&orders](const size_t idx)
			{
				return idx == orders.back().size - 1;
			});
		}
	}
	CanceledOrder.active = false;
	orders.back().active = false;
}

void PrintQuote(const map<int, OrderQueue> &BidPrices, const map<int, OrderQueue> &AskPrices)
{
	cout << "QUOTE ";
	cout << BidPrices.rbegin()->second.total << ' ' << BidPrices.rbegin()->first;
	cout << " - ";
	if (AskPrices.begin()->first == MAX_ASK_PRICE) {
		cout << 0 << ' ' << 99999;
	}
	else {
		cout << AskPrices.begin()->second.total << ' ' << AskPrices.begin()->first;
	}
	cout << endl;
		
}

int main()
{
	bool first = true;
	int n = 0;
	while (cin >> n) {
		if (!first) {
			cout << endl;
		}
		first = false;
		vector<Order> orders;
		map<int, OrderQueue> BidPrices, AskPrices;
		BidPrices[0].append(0, UINT_MAX);
		AskPrices[MAX_ASK_PRICE].append(0, UINT_MAX);
		for (int i = 0; i < n; i++)
		{
			string word;
			cin >> word;
			int size, price, order;
			if (word == "BUY") {
				cin >> size >> price;
				orders.push_back({ OrderType::BUY, size, price, true });
				ProcessBuy(orders, BidPrices, AskPrices);
			}
			else if (word == "SELL") {
				cin >> size >> price;
				orders.push_back({ OrderType::SELL, size, price, true });
				ProcessSell(orders, BidPrices, AskPrices);
			}
			else if (word == "CANCEL") {
				cin >> order;
				orders.push_back({ OrderType::CANCEL, order, order, true });
				ProcessCancel(orders, BidPrices, AskPrices);
			}
			PrintQuote(BidPrices, AskPrices);
		}
	}
	return 0;
}
/*
11
BUY 100 35
CANCEL 1
BUY 100 34
SELL 150 36
SELL 300 37
SELL 100 36
BUY 100 38
CANCEL 4
CANCEL 7
BUY 200 32
SELL 500 30
*/
