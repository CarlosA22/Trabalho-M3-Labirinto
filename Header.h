#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <fstream>   //arquivo
#include <queue>
#include <utility> // pair

using namespace std;

void printMaze(char m[20][20], int& tam1, int& tam2) {
    for (int i = 0; i < tam1; i++) {
        for (int j = 0; j < tam2; j++) {
            cout << m[i][j];
        }
        cout << endl;
    }
}

bool isValid(int& row, int& col, int& tam1, int& tam2) {
    return (row >= 0 && row < tam1 && col >= 0 && col < tam2);
}

/*bool isFree(char m[20][20], int row, int col) {
    return (m[row][col] == ' ' || m[row][col] == '_');
}
*/

bool isFree(char m[20][20], int& row, int& col) {
    return (m[row][col] == '_' || m[row][col] == ' ');
}

bool isSolution(char m[20][20], int row, int col, int endRow, int endCol) {
    return (row == endRow && col == endCol);
}

void findPath(char m[20][20], int tam1, int tam2, int startRow, int startCol, int endRow, int endCol) {
    queue<pair<int, int>> q;
    q.push({ startRow, startCol });

    int dr[] = { -1, 1, 0, 0 }; // Up, Down, Left, Right
    int dc[] = { 0, 0, -1, 1 };

    bool found = false;

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        // Debug output
        cout << "Visiting: (" << row << ", " << col << ")" << endl;
        cout << "Queue size: " << q.size() << endl;

        // Check if we reached the end
        if (isSolution(m, row, col, endRow, endCol)) {
            m[row][col] = 'C';
            found = true;
            break;
        }

        // Check neighbors
        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (isValid(newRow, newCol, tam1, tam2) && isFree(m, newRow, newCol)) {
                q.push({ newRow, newCol });
                m[newRow][newCol] = '.'; // Mark as visited


                // Debug output
                cout << "Adding to queue: (" << newRow << ", " << newCol << ")" << endl;
            }
        }
    }

    // Debug output
    cout << "Search finished. Path " << (found ? "found!" : "not found!") << endl;
    printMaze(m, tam1, tam2);
}

#endif // HEADER_H_INCLUDED