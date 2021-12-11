#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(size_t H, size_t W, istream &is)
		: image(vector<string>(H)), ImageVisitingState(vector<vector<PixelState>>(H, vector<PixelState>(4 * W, PixelState::UNVISITED)))
	{
		for (size_t i = 0; i < H; i++)
		{
			string line;
			is >> line;
			for (char ch : line)
			{
				bitset<4> hex(stoi(string(1, ch), NULL, 16));
				image[i].append(hex.to_string());
			}
		}
		for (size_t i = 0; i < H; i++)
		{
			for (size_t j = 0; j < image[i].length(); j++)
			{
				if (image[i][j] == '1' && ImageVisitingState[i][j] == PixelState::UNVISITED) {
					size_t left = j, right = j, top = i, bottom = i;
					GetCharacterBoundary(i, j, left, right, top, bottom);
					char ch = RecognizeCharacter(left, right, top, bottom);
					CharacterFrequency[ch]++;
				}
			}
		}
	}
	map<char, int> CharacterFrequency;
private:
	enum class PixelState
	{
		UNVISITED, VISITING, VISITED
	};
	vector<string> image, duplicate;
	vector<vector<PixelState>> ImageVisitingState, DupVisitingState;
	static array<string, 16> binary;
	static vector<char> WhiteHole2Character;
	void GetCharacterBoundary(size_t i, size_t j, size_t &left, size_t &right, size_t &top, size_t &bottom)
	{
		if (image[i][j] != '1' || ImageVisitingState[i][j] != PixelState::UNVISITED) return;
		ImageVisitingState[i][j] = PixelState::VISITING;
		left = min(j, left), right = max(j, right);
		top = min(i, top), bottom = max(i, bottom);
		if (i > 0) GetCharacterBoundary(i - 1, j, left, right, top, bottom);
		if (j > 0) GetCharacterBoundary(i, j - 1, left, right, top, bottom);
		if (j + 1 < image[i].length()) GetCharacterBoundary(i, j + 1, left, right, top, bottom);
		if (i + 1 < image.size()) GetCharacterBoundary(i + 1, j, left, right, top, bottom);
	}
	char RecognizeCharacter(size_t left, size_t right, size_t top, size_t bottom)
	{
		size_t row = bottom - top + 3, col = right - left + 3;
		duplicate.assign(row, string(col, '0'));
		DupVisitingState.assign(row, vector<PixelState>(col, PixelState::UNVISITED));
		for (size_t i = top; i <= bottom; i++)
		{
			for (size_t j = left; j <= right; j++)
			{
				if (ImageVisitingState[i][j] == PixelState::VISITING) {
					duplicate[i - top + 1][j - left + 1] = image[i][j];
					ImageVisitingState[i][j] = PixelState::VISITED;
				}
			}
		}

		int WhiteHole = 0;
		for (size_t i = 0; i < duplicate.size(); i++)
		{
			for (size_t j = 0; j < duplicate[i].length(); j++)
			{
				if (duplicate[i][j] == '0' && DupVisitingState[i][j] == PixelState::UNVISITED) {
					CountWhiteHole(i, j);
					WhiteHole++;
				}
			}
		}
		return WhiteHole2Character[WhiteHole - 1];
	}
	void CountWhiteHole(size_t i, size_t j)
	{
		if (duplicate[i][j] != '0' || DupVisitingState[i][j] == PixelState::VISITED) return;
		DupVisitingState[i][j] = PixelState::VISITED;
		if (i > 0) CountWhiteHole(i - 1, j);
		if (j > 0) CountWhiteHole(i, j - 1);
		if (j + 1 < duplicate[i].length()) CountWhiteHole(i, j + 1);
		if (i + 1 < duplicate.size()) CountWhiteHole(i + 1, j);
	}
};

vector<char> Solution::WhiteHole2Character = { 'W', 'A', 'K', 'J', 'S', 'D' };

ostream& operator<<(ostream &os, const Solution &solution)
{
	for (auto p : solution.CharacterFrequency)
	{
		os << string(p.second, p.first);
	}
	return os;
}

int main()
{
	int cases = 0;
	size_t H, W;
	while (cin >> H >> W) {
		if (H == 0 && W == 0) break;
		Solution solution(H, W, cin);
		cout << "Case " << ++cases << ": " << solution << endl;
	}
	return 0;
}
/*

*/
