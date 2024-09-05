#include <iostream>
#include <vector>
using namespace std;

#define LEN 9 


bool is_possible(vector<vector<int>>& board, int row, int col, int val)
{
	for (int i = 0; i < LEN; i++)
	{
		if (board[i][col] == val)
		{
			return false;
		}
	}

	for (int i = 0; i < LEN; i++)
	{
		if (board[row][i] == val)
		{
			return false;
		}
	}
	
	int startRow = 3 * (row / 3); 
	int startCol = 3 * (col / 3);

	for (int i = startRow; i < startRow + 3; i++)
	{
		for (int j = startCol; j < startCol + 3; j++)
		{
			if (board[i][j] == val)
			{
				return false;
			}
		}
	}	
	return true;
}
bool solveSudoku(vector<vector<int>>& board, int row, int col)
{

	if (col == LEN)
	{
		if (row == LEN - 1)
		{
			return true; 
		}
	
		col = 0;
		row++;
	}

	if (board[row][col] != 0) 
	{
		return solveSudoku(board, row, col + 1);
	}

	for (int x = 1; x <= LEN; x++) 
	{
		if (is_possible(board, row, col, x))
		{
			board[row][col] = x;
			if (solveSudoku(board, row, col + 1)) 
			{
				return true;
			}

		}
		board[row][col] = 0; 
	}

	return false;
}
void displayGrid(const vector<vector<int>>& board) {
	for (int row = 0; row < LEN; ++row) {
		for (int col = 0; col < LEN; ++col) {
			cout << board[row][col] << " ";
			if ((col + 1) % 3 == 0 && col < LEN - 1) {
				cout << "| ";
			}
		}
		cout << endl;
		if ((row + 1) % 3 == 0 && row < LEN - 1) {
			cout << "---------------------" << endl;
		}
	}
}

int main() {
	vector<vector<int>> sudokuBoard = {
		{0, 0, 0, 2, 6, 0, 7, 0, 1},
		{ 6, 8, 0, 0, 7, 0, 0, 9, 0 },
		{ 1, 9, 0, 0, 0, 4, 5, 0, 0 },
		{ 8, 2, 0, 1, 0, 0, 0, 4, 0 },
		{ 0, 0, 4, 6, 0, 2, 9, 0, 0 },
		{ 0, 5, 0, 0, 0, 3, 0, 2, 8 },
		{ 0, 0, 9, 3, 0, 0, 0, 7, 4 },
		{ 0, 4, 0, 0, 5, 0, 0, 3, 6 },
		{ 7, 0, 3, 0, 1, 8, 0, 0, 0 },
	};

	cout << "Sudoku Grid:" << endl;
	displayGrid(sudokuBoard);

	bool solved = solveSudoku(sudokuBoard, 0, 0);

	if (solved) {
		cout << "\nSolved Sudoku:" << endl;
		displayGrid(sudokuBoard);
	}
	else {
		cout << "\nNo solution exists." << endl;
	}

	return 0;
}
