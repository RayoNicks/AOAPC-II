#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define DOC_END "**********"
#define QUERY_SEP "----------"
#define QUERY_END "=========="
#define NO_RESULT "Sorry, I found nothing."

using namespace std;

struct Document
{
	vector<string> doc;
};

struct WordEntry
{
	map<size_t, set<size_t>> index;
};

void MergeIndex(const set<size_t> &lines1, const set<size_t> &lines2, vector<size_t> &lines)
{
	auto LineIter1 = lines1.begin(), LineIter2 = lines2.begin();
	while (LineIter1 != lines1.end() && LineIter2 != lines2.end()) {
		if (*LineIter1 < *LineIter2) {
			lines.push_back(*LineIter1);
			LineIter1++;
		}
		else if (*LineIter1 > *LineIter2) {
			lines.push_back(*LineIter2);
			LineIter2++;
		}
		else {
			lines.push_back(*LineIter1);
			LineIter1++, LineIter2++;
		}
	}
	while (LineIter1 != lines1.end()) {
		lines.push_back(*LineIter1);
		LineIter1++;
	}
	while (LineIter2 != lines2.end()) {
		lines.push_back(*LineIter2);
		LineIter2++;
	}
}

map<size_t, vector<size_t>> AndQuery(const WordEntry &idx1, const WordEntry &idx2)
{
	map<size_t, vector<size_t>> result;
	for (auto DocIter1 = idx1.index.begin(); DocIter1 != idx1.index.end(); DocIter1++)
	{
		auto DocIter2 = idx2.index.find(DocIter1->first);
		if (DocIter2 != idx2.index.end()) {
			MergeIndex(DocIter1->second, DocIter2->second, result[DocIter1->first]);
		}
	}
	return result;
}

map<size_t, vector<size_t>> OrQuery(const WordEntry &idx1, const WordEntry &idx2)
{
	map<size_t, vector<size_t>> result;
	auto DocIter1 = idx1.index.begin(), DocIter2 = idx2.index.begin();
	while (DocIter1 != idx1.index.end() && DocIter2 != idx2.index.end()) {
		if (DocIter1->first < DocIter2->first) {
			for (size_t no : DocIter1->second)
			{
				result[DocIter1->first].push_back(no);
			}
			DocIter1++;
		}
		else if (DocIter1->first > DocIter2->first) {
			for (size_t no : DocIter2->second)
			{
				result[DocIter2->first].push_back(no);
			}
			DocIter2++;
		}
		else {
			MergeIndex(DocIter1->second, DocIter2->second, result[DocIter1->first]);
			DocIter1++, DocIter2++;
		}
	}
	while (DocIter1 != idx1.index.end()) {
		for (size_t no : DocIter1->second)
		{
			result[DocIter1->first].push_back(no);
		}
		DocIter1++;
	}
	while (DocIter2 != idx2.index.end()) {
		for (size_t no : DocIter2->second)
		{
			result[DocIter2->first].push_back(no);
		}
		DocIter2++;
	}
	return result;
}

map<size_t, vector<size_t>> NotQuery(const WordEntry &idx, const vector<Document> &docs)
{
	map<size_t, vector<size_t>> result;
	for (size_t i = 0; i < docs.size(); i++)
	{
		if (idx.index.find(i) == idx.index.end()) {
			vector<size_t> &lines = result[i];
			for (size_t j = 0; j < docs[i].doc.size(); j++)
			{
				lines.push_back(j);
			}
		}
	}
	return result;
}

map<size_t, vector<size_t>> NormalQuery(const WordEntry &idx)
{
	map<size_t, vector<size_t>> result;
	for (auto DocIter = idx.index.begin(); DocIter != idx.index.end(); DocIter++)
	{
		for (size_t no : DocIter->second)
		{
			result[DocIter->first].push_back(no);
		}
	}
	return result;
}

void OutputResult(const map<size_t, vector<size_t>> &result, const vector<Document> &docs)
{
	if (result.empty()) {
		cout << NO_RESULT << endl;
	}
	else {
		for (auto iter = result.begin(); iter != result.end(); iter++)
		{
			if (iter != result.begin()) {
				cout << QUERY_SEP << endl;
			}
			for (size_t no : iter->second)
			{
				cout << docs[iter->first].doc[no] << endl;
			}
		}
	}
	cout << QUERY_END << endl;
}

int main()
{
	size_t N = 0, M = 0;
	vector<Document> docs;
	map<string, WordEntry> InvertedIndex;
	cin >> N;
	cin.get();
	for (size_t n = 0; n < N; n++)
	{
		string line;
		size_t no = 0;
		docs.push_back(Document{ vector<string>() });
		while (getline(cin, line)) {
			if (line == DOC_END) break;
			docs.back().doc.push_back(line);
			string::iterator b = line.begin(), e;
			while (b != line.end()) {
				b = find_if(b, line.end(), [](const char &ch) { return isalpha(ch); });
				e = find_if(b, line.end(), [](const char &ch) { return !isalpha(ch); });
				string word;
				for (auto iter = b; iter != e; iter++)
				{
					word.push_back(tolower(*iter));
				}
				b = e;
				InvertedIndex[word].index[n].insert(no);
			}
			no++;
		}
	}
	cin >> M;
	cin.get();
	string query, term1, term2;
	size_t pos;
	for (size_t m = 0; m < M; m++)
	{
		vector<size_t> ret;
		getline(cin, query);
		map<size_t, vector<size_t>> result;
		if ((pos = query.find("AND"))!= string::npos) {
			term1.assign(query.substr(0, pos - 1));
			term2.assign(query.substr(pos + 4));
			const WordEntry &idx1 = InvertedIndex[term1];
			const WordEntry &idx2 = InvertedIndex[term2];
			result = AndQuery(idx1, idx2);
		}
		else if ((pos = query.find("OR")) != string::npos) {
			term1.assign(query.substr(0, pos - 1));
			term2.assign(query.substr(pos + 3));
			const WordEntry &idx1 = InvertedIndex[term1];
			const WordEntry &idx2 = InvertedIndex[term2];
			result = OrQuery(idx1, idx2);
		}
		else if ((pos = query.find("NOT")) != string::npos) {
			term1.assign(query.substr(pos + 4));
			const WordEntry &idx = InvertedIndex[term1];
			result = NotQuery(idx, docs);
		}
		else {
			term1.assign(query);
			const WordEntry &idx = InvertedIndex[term1];
			result = NormalQuery(idx);
		}
		OutputResult(result, docs);
	}
	return 0;
}
/*
4
A manufacturer, importer, or seller of
digital media devices may not (1) sell,
or offer for sale, in interstate commerce,
or (2) cause to be transported in, or in a
manner affecting, interstate commerce,
a digital media device unless the device
includes and utilizes standard security
technologies that adhere to the security
system standards.
**********
Of course, Lisa did not necessarily
intend to read his books. She might
want the computer only to write her
midterm. But Dan knew she came from
a middle-class family and could hardly
afford the tuition, let alone her reading
fees. Books might be the only way she
could graduate
**********
Research in analysis (i.e., the evaluation
of the strengths and weaknesses of
computer system) is essential to the
development of effective security, both
for works protected by copyright law
and for information in general. Such
research can progress only through the
open publication and exchange of
complete scientific results
**********
I am very very very happy!
What about you?
**********
6
computer
books AND computer
books OR protected
NOT security
very
slick
*/
