#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <iomanip>

#define CLASSES 21
#define COURSES 4
#define CHINESE 0
#define MATH 1
#define ENGLISH 2
#define PROGRAMMING 3
#define OVERALL_TYPE 5
#define PASSED_SCORE 60
#define PASSED_ALL 0
#define PASSED_3 1
#define PASSED_2 2
#define PASSED_1 3
#define FAILED_ALL 4

#define EPS 1e-5

using namespace std;

typedef struct Info
{
	string strSID;
	string strName;
	int iCID;
	int iScore[COURSES];
	int iSum;
	int iRank;
	int iOrder;
}Info;

list<Info> lstInfo;
int iOrder = 0;

const vector<string> vecstrClass = { "Chinese", "Mathematics", "English", "Programming" };

int selMenu()
{
	cout << "Welcome to Student Performance Management System (SPMS).\n\n";
	cout << "1 - Add\n";
	cout << "2 - Remove\n";
	cout << "3 - Query\n";
	cout << "4 - Show ranking\n";
	cout << "5 - Show Statistics\n";
	cout << "0 - Exit\n";
	cout << endl;
	int iSel;
	cin >> iSel;
	return iSel;
}

bool checkQuit(const string &strInput)
{
	if (strInput.size() == 1 && strInput[0] == '0') return true;
	else return false;
}

bool checkDup(const string &strSID)
{
	for (auto iter = lstInfo.begin(); iter != lstInfo.end(); iter++)
	{
		if (iter->strSID == strSID){
			return true;
		}
	}
	return false;
}

void insertInfo(const Info &info)
{
	for (auto iter = lstInfo.begin(); iter != lstInfo.end(); iter++)
	{
		if (iter->iSum < info.iSum){
			lstInfo.insert(iter, info);
			return;
		}
	}
	lstInfo.push_back(info);
	return;
}

void add()
{
	while (1){
		cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish.\n";
		Info info;
		cin >> info.strSID;
		if (checkQuit(info.strSID)) return;
		cin >> info.iCID;
		cin.get();
		cin >> info.strName;
		info.iSum = 0;
		for (int i = 0; i < sizeof(info.iScore) / sizeof(int); i++)
		{
			cin >> info.iScore[i];
			info.iSum += info.iScore[i];
		}
		if (checkDup(info.strSID)){
			cout << "Duplicated SID.\n";
			continue;
		}
		info.iOrder = iOrder++;
		insertInfo(info);
	}
}

void remove()
{
	string strInput;
	while (1){
		cout << "Please enter SID or name. Enter 0 to finish.\n";
		cin >> strInput;
		if (checkQuit(strInput)) return;
		int cnt = 0;
		for (auto iter = lstInfo.begin(); iter != lstInfo.end();)
		{
			if (iter->strSID == strInput || iter->strName == strInput){
				iter = lstInfo.erase(iter);
				cnt++;
			}
			else iter++;
		}
		cout << cnt << " student(s) removed.\n";
	}
}

void printRank(const Info &info)
{
	cout << info.iRank << ' ' << info.strSID << ' ' << info.iCID << ' '
		<< info.strName << ' ';
	for (int i = 0; i < COURSES; i++)
	{
		cout << info.iScore[i] << ' ';
	}
	cout << info.iSum << ' ';
	double dAvg = ((double)info.iSum) / COURSES + EPS;
	cout << setprecision(2) << fixed << dAvg + EPS << endl;
}

void query()
{
	string strInput;
	while (1){
		cout << "Please enter SID or name. Enter 0 to finish.\n";
		cin >> strInput;
		if (checkQuit(strInput)) return;
		size_t idx = 1, rank = 0;
		int sum = 401;
		vector<Info> vecTmp;
		for (auto iter = lstInfo.begin(); iter != lstInfo.end(); iter++, idx++)
		{
			if (iter->iSum != sum){
				rank = idx;
				sum = iter->iSum;
			}
			iter->iRank = rank;
			if (iter->strSID == strInput || iter->strName == strInput){
				vecTmp.push_back(*iter);
			}
		}
		sort(vecTmp.begin(), vecTmp.end(),
			[](const Info &i1, const Info &i2)->bool{return i1.iOrder < i2.iOrder; });
		for_each(vecTmp.begin(), vecTmp.end(), printRank);
	}
}

void showRank()
{
	cout << "Showing the ranklist hurts students' self-esteem. Don't do that.\n";
	return;
}

void showStatistic()
{
	int iCID;
	cout << "Please enter class ID, 0 for the whole statistics.\n";
	cin >> iCID;
	//二维数组表示每个班级该课程的统计数据
	//第一维取0表示所有班级
	vector<vector<int>> vviSum(CLASSES, vector<int>(COURSES, 0));
	vector<vector<int>> vviPassed(CLASSES, vector<int>(COURSES, 0));
	vector<vector<int>> vviFailed(CLASSES, vector<int>(COURSES, 0));
	vector<vector<int>> vviOverall(CLASSES, vector<int>(OVERALL_TYPE, 0));
	vector<int> viTotalStudent(CLASSES, 0);
	for (auto iter = lstInfo.begin(); iter != lstInfo.end(); iter++)
	{
		//更新学生总数
		viTotalStudent[0]++;
		viTotalStudent[iter->iCID]++;
		int iPassedCnt = 0;
		for (int course = CHINESE; course <= PROGRAMMING; course++)
		{
			//更新该课程总成绩
			vviSum[0][course] += iter->iScore[course];
			vviSum[iter->iCID][course] += iter->iScore[course];
			//更新及格情况
			if (iter->iScore[course] >= PASSED_SCORE){
				vviPassed[0][course]++;
				vviPassed[iter->iCID][course]++;
				iPassedCnt++ ;
			}
			else{
				vviFailed[0][course]++;
				vviFailed[iter->iCID][course]++;
			}
		}
		//更新通过情况
		switch (iPassedCnt)
		{
		case 4:
			vviOverall[0][PASSED_ALL]++;
			vviOverall[iter->iCID][PASSED_ALL]++;
		case 3:
			vviOverall[0][PASSED_3]++;
			vviOverall[iter->iCID][PASSED_3]++;
		case 2:
			vviOverall[0][PASSED_2]++;
			vviOverall[iter->iCID][PASSED_2]++;
		case 1:
			vviOverall[0][PASSED_1]++;
			vviOverall[iter->iCID][PASSED_1]++;
			break;
		case 0:
			vviOverall[0][FAILED_ALL]++;
			vviOverall[iter->iCID][FAILED_ALL]++;
			break;
		}
	}
	double dAvg = 0.0;
	for (int i = 0; i < COURSES; i++)
	{
		cout << vecstrClass[i] << endl;
		if (viTotalStudent[iCID] == 0) cout << "Average Score: -nan" << endl;
		else cout << "Average Score: " << setprecision(2) << fixed << ((double)vviSum[iCID][i]) / viTotalStudent[iCID] + EPS << endl;
		cout << "Number of passed students: " << vviPassed[iCID][i] << endl;
		cout << "Number of failed students: " << vviFailed[iCID][i] << endl;
		cout << endl;
	}
	cout << "Overall:\n";
	cout << "Number of students who passed all subjects: " << vviOverall[iCID][PASSED_ALL] << endl;
	cout << "Number of students who passed 3 or more subjects: " << vviOverall[iCID][PASSED_3] << endl;
	cout << "Number of students who passed 2 or more subjects: " << vviOverall[iCID][PASSED_2] << endl;
	cout << "Number of students who passed 1 or more subjects: " << vviOverall[iCID][PASSED_1] << endl;
	cout << "Number of students who failed all subjects: " << vviOverall[iCID][FAILED_ALL] << endl;
	cout << endl;
}

int main()
{
	int iSel = 0;
	while (1){
		iSel = selMenu();
		if (iSel == 0) break;
		switch (iSel)
		{
		case 1:
			add();
			break;
		case 2:
			remove();
			break;
		case 3:
			query();
			break;
		case 4:
			showRank();
			break;
		case 5:
			showStatistic();
			break;
		}
	}
	return 0;
}
/*
1
0011223344 1 John 79 98 91 100
0022334455 1 Tom 59 72 60 81
0011223344 2 Alice 100 100 100 100
2423475629 2 John 60 80 30 99
0
3
0022334455
John
0
5
1
2
0011223344
0
5
0
4
0
*/
