#include <iostream>
#include "Header.h"

using namespace std;

int main() {
	int tam1 = 20, tam2 = 20;

	char map[20][20] =
	{
		'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X','_','_','X','_','_','_','_','_','_','_','_','_','_','_','_','_','X','X','X',
		'_','_','X','X','_','X','X','X','X','X','X','X','X','X','X','X','_','_','X','X',
		'X','_','_','_','_','X','X','_','_','_','_','X','_','_','_','X','X','_','X','X',
		'X','X','X','X','X','X','X','X','_','_','_','X','X','X','X','X','X','_','X','X',
		'X','_','_','_','_','_','X','X','_','_','_','_','_','_','_','_','X','_','X','X',
		'X','_','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','_','X','X',
		'X','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','X','X',
		'X','X','X','X','X','X','_','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X','_','X','_','X','X','_','X','_','_','_','_','_','_','_','_','_','_','_','X',
		'X','_','X','_','X','X','_','X','X','X','X','X','X','X','X','X','_','X','X','X',//Q
		'X','_','X','_','X','X','_','_','_','_','_','_','_','_','_','_','_','_','_','X',
		'X','X','X','_','X','X','X','X','X','X','X','X','X','_','X','X','X','X','X','X',
		'X','_','_','_','_','_','_','_','_','X','X','X','X','_','X','_','_','_','_','X',
		'X','_','X','X','_','X','X','X','_','_','_','_','_','_','X','_','_','_','_','X',
		'X','_','X','X','_','X','_','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X','_','X','_','_','X','_','_','_','_','_','_','_','_','_','_','_','_','_','_',
		'X','X','X','_','X','X','_','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X','_','X','_','_','_','_','X','_','_','_','_','_','_','_','_','_','_','_','X',
		'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
	};
	// Print the original maze
	cout << "Original Maze:" << endl;
	printMaze(map, tam1, tam2);

	// Get user input for start and end positions (1-based indexing)
	int startRow, startCol, endRow, endCol;
	cout << "Enter starting row and column (1-based, separated by a space): ";
	cin >> startRow >> startCol;

	cout << "Enter ending row and column (1-based, separated by a space): ";
	cin >> endRow >> endCol;

	// Convert to 0-based indexing
	startRow--;
	startCol--;
	endRow--;
	endCol--;


	// Check if the start and end positions are valid
	if (!isValid(startRow, startCol, tam1, tam2) || !isValid(endRow, endCol, tam1, tam2)) {
		cerr << "Invalid start or end position!" << endl;
		return 1;
	}

	// Check if the start and end positions are free
	if (!isFree(map, startRow, startCol) || !isFree(map, endRow, endCol)) {
		cerr << "Start or end position is not free!" << endl;
		return 1;
	}

	// Find and print the path
	findPath(map, tam1, tam2, startRow, startCol, endRow, endCol);
	return 0;
}
