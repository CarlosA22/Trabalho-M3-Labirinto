#include <iostream>
#include "Header.h"

using namespace std;

int main() {
	ifstream labFile;
	labFile.open("lab01.txt");

	if (!labFile) {
		cerr << "Error opening file!" << endl;
		return 1;
	}

	int tam1 = 20, tam2 = 20;
	//labFile >> tam1 >> tam2;

	char maze[MAX_SIZE][MAX_SIZE];

	char map[20][20] =
	{
		'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','X',
		' ',' ','X','X',' ','X','X','X','X','X','X','X','X','X','X','X',' ',' ','X','X',
		'X',' ',' ',' ',' ','X','X',' ',' ',' ',' ','X',' ',' ',' ','X','X',' ','X','X',
		'X','X','X','X','X','X','X','X',' ',' ',' ','X','X','X','X','X','X',' ','X','X',
		'X',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X','X',
		'X',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',' ','X','X',
		'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X',
		'X','X','X','X','X','X',' ','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X',' ','X',' ','X','X',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
		'X',' ','X',' ','X','X',' ','X','X','X','X','X','X','X','X','X',' ','X','X','X', //Q
		'X',' ','X',' ','X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
		'X','X','X',' ','X','X','X','X','X','X','X','X','X',' ','X','X','X','X','X','X',
		'X',' ',' ',' ',' ',' ',' ',' ',' ','X','X','X','X',' ','X',' ',' ',' ',' ','X',
		'X',' ','X','X',' ','X','X','X',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ','X',
		'X',' ','X','X',' ','X',' ','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X',' ','X',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
		'X','X','X',' ','X','X',' ','X','X','X','X','X','X','X','X','X','X','X','X','X',
		'X',' ','X',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
		'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
	}

		// Read the labyrinth from the file with debug output
		/*for (int i = 0; i < tam1; i++) {
			for (int j = 0; j < tam2; j++) {
				labFile >> maze[i][j];
			}
			cout << endl; // Debug output
		}

		*/
		//labFile.close();

		// Print the original maze
	cout << "Original Maze:" << endl;
	printMaze(maze, tam1, tam2);

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

	// Debug output to print the content of the maze before user input
	cout << "Maze Content:" << endl;
	printMaze(maze, tam1, tam2);

	// Check if the start and end positions are valid
	if (!isValid(startRow, startCol, tam1, tam2) || !isValid(endRow, endCol, tam1, tam2)) {
		cerr << "Invalid start or end position!" << endl;
		return 1;
	}

	// Check if the start and end positions are free
	if (!isFree(maze, startRow, startCol) || !isFree(maze, endRow, endCol)) {
		cerr << "Start or end position is not free!" << endl;
		return 1;
	}


	// Find and print the path
	findPath(maze, tam1, tam2, startRow, startCol, endRow, endCol); // can't find path after 12 13.

	labFile.close();
	return 0;
}
