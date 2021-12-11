#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef struct Piece
{
	char ch;
	int x, y;
}Piece;

bool checkG(int begin, int end, int y, const vector<vector<bool>> &vvcBoard)
{
	for (int i = begin; i <= end; i++)
	{
		if (vvcBoard[i][y]) return false;
	}
	return true;
}

bool checkR(const Piece &R, int x, int y, const vector<vector<bool>> &vvcBoard)
{
	//left
	for (int col = R.y - 1; col >= y; col--)
	{
		if (vvcBoard[R.x][col]) break;
		if (R.x == x && col == y) return true;
	}
	//up
	for (int row = R.x - 1; row >= x; row--)
	{
		if (vvcBoard[row][R.y]) break;
		if (row == x && R.y == y) return true;
	}
	//right
	for (int col = R.y + 1; col <= y; col++)
	{
		if (vvcBoard[R.x][col]) break;
		if (R.x == x && col == y) return true;
	}
	//down
	for (int row = R.x + 1; row <= x; row++)
	{
		if (vvcBoard[row][R.y]) break;
		if (row == x && R.y == y) return true;
	}
	return false;
}

bool checkH(const Piece &H, int x, int y, const vector<vector<bool>> &vvcBoard)
{
	//up left
	if (H.x - 1 >= 1 && !vvcBoard[H.x - 1][H.y] && H.x - 2 == x && H.y - 1 == y) return true;
	//up right
	if (H.x - 1 >= 1 && !vvcBoard[H.x - 1][H.y] && H.x - 2 == x && H.y + 1 == y) return true;
	//right up
	if (H.y + 1 <= 9 && !vvcBoard[H.x][H.y + 1] && H.x - 1 == x && H.y + 2 == y) return true;
	//right down
	if (H.y + 1 <= 9 && !vvcBoard[H.x][H.y + 1] && H.x + 1 == x && H.y + 2 == y) return true;
	//down right
	if (H.x + 1 <= 10 && !vvcBoard[H.x + 1][H.y] && H.x + 2 == x && H.y + 1 == y) return true;
	//down left
	if (H.x + 1 <= 10 && !vvcBoard[H.x + 1][H.y] && H.x + 2 == x && H.y - 1 == y) return true;
	//left down
	if (H.y - 1 >= 1 && !vvcBoard[H.x][H.y - 1] && H.x + 1 == x && H.y - 2 == y) return true;
	//left up
	if (H.y - 1 >= 1 && !vvcBoard[H.x][H.y - 1] && H.x - 1 == x && H.y - 2 == y) return true;
	return false;
}

bool checkC(const Piece &H, int x, int y, const vector<vector<bool>> &vvcBoard)
{
	//left
	int left = 0, up = 0, right = 0, down = 0;
	for (int col = H.y - 1; col > y; col--)
	{
		if (vvcBoard[H.x][col]) left++;
	}
	if (left == 1) return true;
	//up
	for (int row = H.x - 1; row > x; row--)
	{
		if (vvcBoard[row][H.y]) up++;
	}
	if (up == 1) return true;
	//right
	for (int col = H.y + 1; col < y; col++)
	{
		if (vvcBoard[H.x][col]) right++;
	}
	if (right == 1) return true;
	//down
	for (int row = H.x + 1; row < x; row++)
	{
		if (vvcBoard[row][H.y]) down++;
	}
	if (down == 1) return true;
	return false;
}

bool check(int x, int y, const vector<Piece> &vecRed, vector<vector<bool>> vvcBoard)
{
	if (x < 1 || x > 3 || y < 4 || y > 6) return true;
	vvcBoard[x][y] = false;
	for (const Piece &piece : vecRed)
	{
		//红子被吃了
		if (piece.x == x && piece.y == y) continue;
		else{
			switch (piece.ch)
			{
			case 'G':
				if (y == piece.y && 
					checkG(x + 1, piece.x - 1, y, vvcBoard)) return true;
				else break;
			case 'R':
				if ((y == piece.y || x == piece.x) &&
					checkR(piece, x, y, vvcBoard)) return true;
				else break;
			case 'H':
				if (checkH(piece, x, y, vvcBoard)) return true;
				else break;
			case 'C':
				if ((y == piece.y || x == piece.x) &&
					checkC(piece, x, y, vvcBoard)) return true;
				else break;
			default:
				break;
			}
		}
	}
	return false;
}

bool check(const Piece &black, const vector<Piece> &vecRed, const vector<vector<bool>> &vvcBoard)
{
	/*
	黑子的范围为(1, 4)、(3, 6)两点组成的矩形
	*/for (const Piece &piece : vecRed)
	{
		if (piece.ch == 'G' &&
			black.y == piece.y &&
			checkG(black.x + 1, piece.x - 1, black.y, vvcBoard)) return false;
	}
	bool bCheckMate = check(black.x - 1, black.y, vecRed, vvcBoard) &
		check(black.x + 1, black.y, vecRed, vvcBoard) &
		check(black.x, black.y - 1, vecRed, vvcBoard) &
		check(black.x, black.y + 1, vecRed, vvcBoard);
	return bCheckMate;
}

int main()
{
	int red = 0;
	Piece black;
	black.ch = 'G';
	while (cin >> red >> black.x >> black.y){
		if (red == 0 && black.x == 0 && black.y == 0) break;
		vector<Piece> vecRed;
		Piece piece;
		vector<vector<bool>> vvcBoard(11, vector<bool>(10, false));
		for (int i = 0; i < red; i++)
		{
			cin >> piece.ch;
			cin >> piece.x >> piece.y;
			vecRed.push_back(piece);
			vvcBoard[piece.x][piece.y] = true;
			cin.get();
		}
		cin.get();
		if (check(black, vecRed, vvcBoard)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
/*
2 1 4
G 10 5
R 6 4

3 1 5
H 4 5
G 10 5
C 7 5

0 0 0
*/
