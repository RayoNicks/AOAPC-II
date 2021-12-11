#include <iostream>
#include <string>
#include <vector>

using namespace std;

unsigned int IP2UI(const string &strIP)
{
	unsigned int uiIP = 0, uiBits = 24, ui;
	string::size_type posDot, begin = 0;
	while ((posDot = strIP.find('.', begin)) != string::npos){
		ui = stoul(strIP.substr(begin, posDot));
		begin = posDot + 1;
		uiIP |= ui << uiBits;
		uiBits -= 8;
	}
	ui = stoul(strIP.substr(begin));
	uiIP |= ui << uiBits;
	return uiIP;
}

string UI2IP(unsigned int uiIP)
{
	string strIP;
	for (size_t cnt = 0; cnt < 4; cnt++)
	{
		strIP += to_string((uiIP >> (24 - cnt * 8)) & 0xFF);
		strIP.push_back('.');
	}
	strIP.pop_back();
	return strIP;
}

unsigned int getMask(unsigned int uiIP1, unsigned int uiIP2)
{
	for (unsigned int uiMask = 0xFFFFFFFF; uiMask != 0; uiMask <<= 1)
	{
		if ((uiMask & uiIP1) == (uiMask & uiIP2)) return uiMask;
	}
	return 0;
}

unsigned int mergeMask(unsigned int uiIP1, unsigned int uiIP2, unsigned uiMask)
{
	for (; uiMask != 0; uiMask <<= 1)
	{
		if ((uiIP1 & uiMask) == (uiIP2 & uiMask)) return uiMask;
	}
	return 0;
}

unsigned int getMask(const vector<unsigned int> &vecIP, size_t begin, size_t end)
{
	unsigned int uiLMask, uiRMask;
	size_t mid = (begin + end) >> 1;
	if (end - begin == 1){
		return 0xFFFFFFFF;
	}
	if (end - begin == 2){
		return getMask(vecIP[begin], vecIP[end - 1]);
	}
	else{
		uiLMask = getMask(vecIP, begin, mid);
		uiRMask = getMask(vecIP, mid, end);
		if (uiLMask <= uiRMask) return mergeMask(vecIP[begin], vecIP[mid], uiLMask);
		else return mergeMask(vecIP[begin], vecIP[mid], uiRMask);
	}
}

int main()
{
	int m = 0;
	while (cin >> m){
		cin.get();
		string strIP;
		vector<unsigned int> vecIP;
		for (int i = 0; i < m; i++)
		{
			cin >> strIP;
			vecIP.push_back(IP2UI(strIP));
		}
		unsigned int uiMask = getMask(vecIP, 0, vecIP.size());
		string strMask = UI2IP(uiMask);
		string strNet = UI2IP(uiMask & vecIP[0]);
		cout << strNet << endl << strMask << endl;
	}
	return 0;
}
/*
3
194.85.160.177
194.85.160.183
194.85.160.178
*/
