#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <windows.h> //cursor
#include <conio.h>   //_getch
#include <fstream>   //arquivo
#include <stdlib.h>  //random
#include <string>
#include <queue>
#include <utility> // pair

using namespace std;

void colorir(int cor)
{

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(out, cor);
}

const int MAX_SIZE = 20;

void printMaze(char m[MAX_SIZE][MAX_SIZE], int tam1, int tam2) {
    for (int i = 0; i < tam1; i++) {
        for (int j = 0; j < tam2; j++) {
            cout << m[i][j];
        }
        cout << endl;
    }
}

bool isValid(int row, int col, int tam1, int tam2) {
    return (row >= 0 && row < tam1 && col >= 0 && col < tam2);
}

/*bool isFree(char m[MAX_SIZE][MAX_SIZE], int row, int col) {
    return (m[row][col] == ' ' || m[row][col] == '_');
}
*/

bool isFree(char m[MAX_SIZE][MAX_SIZE], int row, int col) {
    return (m[row][col] == ' ' || m[row][col] == '_' || m[row][col] == 'X');
}


bool isSolution(char m[MAX_SIZE][MAX_SIZE], int row, int col, int endRow, int endCol) {
    return (row == endRow && col == endCol);
}

void findPath(char m[MAX_SIZE][MAX_SIZE], int tam1, int tam2, int startRow, int startCol, int endRow, int endCol) {
    queue<pair<int, int>> q;
    q.push({ startRow, startCol });
    int dr[] = { -1, 1, 0, 0 }; // Up, Down, Left, Right
    int dc[] = { 0, 0, -1, 1 };

    bool found = false; // Flag to check if the destination is reached

    while (!q.empty() && !found) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        // Check if we reached the end
        if (isSolution(m, row, col, endRow, endCol)) {
            m[row][col] = 'E'; // Mark as part of the path
            found = true;
            break;
        }

        // Check neighbors
        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (isValid(newRow, newCol, tam1, tam2) && isFree(m, newRow, newCol)) {
                q.push({ newRow, newCol });
                m[newRow][newCol] = 'v'; // Mark as visited
            }
        }
    }

    // Trace back the path
    if (found) {
        int row = endRow;
        int col = endCol;

        while (row != startRow || col != startCol) {
            m[row][col] = 'P'; // Mark as part of the path
            int tmpRow = row;
            int tmpCol = col;

            for (int i = 0; i < 4; i++) {
                int newRow = tmpRow + dr[i];
                int newCol = tmpCol + dc[i];

                if (isValid(newRow, newCol, tam1, tam2) && m[newRow][newCol] == 'v') {
                    row = newRow;
                    col = newCol;
                    break;
                }
            }
        }

        m[startRow][startCol] = 'P'; // Mark the start as part of the path
    }
    else {
        cout << "There is no path from start to end!" << endl;
        return;
    }

    // Print the maze with the path
    cout << "Path Found!" << endl;
    printMaze(m, tam1, tam2);
}

#endif // HEADER_H_INCLUDED