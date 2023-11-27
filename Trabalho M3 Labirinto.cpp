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

    int tam1, tam2;
    labFile >> tam1 >> tam2;

    char maze[MAX_SIZE][MAX_SIZE];

    // Read the labyrinth from the file
    for (int i = 0; i < tam1; i++) {
        for (int j = 0; j < tam2; j++) {
            labFile >> maze[i][j];
            cout << maze[i][j] << ' ';  // Debug output
        }
        cout << endl;  // Debug output
    }

    labFile.close();

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

    // Check if the start and end positions are valid
    if (!isValid(startRow, startCol, tam1, tam2) || !isValid(endRow, endCol, tam1, tam2) ||
        !isFree(maze, startRow, startCol) || !isFree(maze, endRow, endCol)) {
        cerr << "Invalid start or end position!" << endl;
        return 1;
    }

    // Find and print the path
    findPath(maze, tam1, tam2, startRow, startCol, endRow, endCol);

    return 0;
}