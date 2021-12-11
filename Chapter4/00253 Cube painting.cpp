#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

string rotate(const string &strCube, const vector<int> &viPermutation)
{
	string strRet(strCube.size(), '\0');
	for (size_t i = 0; i < strCube.size(); i++)
	{
		strRet[i] = strCube[viPermutation[i] - 1];
	}
	return strRet;
}

set<string> generate(const string &strCube)
{
	static const vector<int> viFrontBackClockwise = { 3, 2, 6, 1, 5, 4 };
	static const vector<int> viFrontBackAntiClockwise = { 4, 2, 1, 6, 5, 3 };
	static const vector<int> viLeftRightClockwise = { 5, 1, 3, 4, 6, 2 };
	static const vector<int> viLeftRightAntiClockwise = { 2, 6, 3, 4, 1, 5 };
	static const vector<int> viUpDownClockwise = { 1, 4, 2, 5, 3, 6 };
	static const vector<int> viUpDownAntiClockwise = { 1, 3, 5, 2, 4, 6 };
	set<string> sstr;
	//1在上的4种排列
	string strTmp(strCube);
	sstr.insert(strTmp);
	for (size_t i = 0; i < 3; i++)
	{
		strTmp = rotate(strTmp, viUpDownClockwise);
		sstr.insert(strTmp);
	}
	//2在上的4种排列
	strTmp = rotate(strCube, viLeftRightAntiClockwise);
	sstr.insert(strTmp);
	for (size_t i = 0; i < 3; i++)
	{
		strTmp = rotate(strTmp, viUpDownClockwise);
		sstr.insert(strTmp);
	}
	//3在上的4种排列
	strTmp = rotate(strCube, viFrontBackClockwise);
	sstr.insert(strTmp);
	for (size_t i = 0; i < 3; i++)
	{
		strTmp = rotate(strTmp, viUpDownClockwise);
		sstr.insert(strTmp);
	}
	//4在上的4种排列
	strTmp = rotate(strCube, viFrontBackAntiClockwise);
	sstr.insert(strTmp);
	for (size_t i = 0; i < 3; i++)
	{
		strTmp = rotate(strTmp, viUpDownClockwise);
		sstr.insert(strTmp);
	}
	//5在上的4种排列
	strTmp = rotate(strCube, viLeftRightClockwise);
	sstr.insert(strTmp);
	for (size_t i = 0; i < 3; i++)
	{
		strTmp = rotate(strTmp, viUpDownClockwise);
		sstr.insert(strTmp);
	}
	//6在上的4种排列
	strTmp = rotate(strCube, viFrontBackClockwise);
	strTmp = rotate(strTmp, viFrontBackClockwise);
	sstr.insert(strTmp);
	for (size_t i = 0; i < 3; i++)
	{
		strTmp = rotate(strTmp, viUpDownClockwise);
		sstr.insert(strTmp);
	}
	return sstr;
}

int main()
{
	string strLine, strCube1, strCube2;
	while (getline(cin, strLine)){
		strCube1 = strLine.substr(0, 6);
		strCube2 = strLine.substr(6, 6);
		set<string> sstr = generate(strCube1);
		if (sstr.find(strCube2) != sstr.end()){
			cout << "TRUE" << endl;
		}
		else cout << "FALSE" << endl;
	}
	return 0;
}
/*
rbgggrrggbgr
rrrbbbrrbbbr
rbgrbgrrrrrg
*/
