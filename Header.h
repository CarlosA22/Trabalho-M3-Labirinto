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

struct MAPA
{
	const char* arquivo;
	int posicaox, posicaoy;

	void carregaMAPA(char m[20][20], int& x, int& y)
	{
		ifstream stream;
		stream.open(arquivo);

		if (stream.is_open())
		{
			stream >> posicaox;
			stream >> posicaoy;
			x = posicaox;
			y = posicaoy;

			if (strcmp(arquivo, "lab01.txt") == 0)
			{
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						stream >> m[i][j];
					}
				}
			}
			else
			{
				cout << "Arquivo de mapa inválido." << endl;
			}
		}
		else
		{
			cout << "Erro ao abrir o arquivo" << endl;
		}
		stream.close();
	}


};

void colorir(int cor)
{

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, cor);
}

/*void criarMapa()
{
	ofstream lab01;
	lab01.open("lab01.txt");
	char m[10][10];
	int tamanho = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cin >> m[i][j];
			lab01 << m[i][j];
		}
		lab01 << endl;
	}
	lab01.close();

}
*/
/*void imprimirMapa()
{
	ifstream lab01;
	lab01.open("lab01.txt");
	char m[10][10];
	string linhaTamanho;
	int tam1 = 0, tam2 = 0;


	//getline(lab01, linhaTamanho, '\n');
	lab01 >> linhaTamanho;
	tam1 = stoi(linhaTamanho);
	//getline(lab01, linhaTamanho, '\n');
	lab01 >> linhaTamanho;
	tam2 = stoi(linhaTamanho);
	//cout<< tam1 << tam2 << endl;

	// Verifica se as dimensoes estao dentro dos limites da matriz
	// Se nao estiverem, retorna erro e fecha o arquivo
	// isso nao deve funcionar como eu espero...
	if (tam1 > 10 || tam2 > 10)
	{
		cout << "Erro: as dimensoes da matriz excedem o tamanho da matriz." << endl;
		lab01.close();
		return;
	}

	// Ler dados na matriz
	for (int i = 0; i < tam1; i++)
	{
		for (int j = 0; j < tam2; j++)
		{
			if (lab01 >> m[i][j])
			{
				cout << m[i][j];
			}
			else
			{
				cout << "Erro ao ler dados do arquivo." << endl;
				lab01.close();
				return;
			}
		}
	}



	lab01.close();
}
*/

const int MAX_SIZE = 20;

void printMaze(char m[MAX_SIZE][MAX_SIZE], int tam1, int tam2) {
	for (int i = 0; i < tam1; i++) {
		for (int j = 0; j < tam2; j++) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
}

bool isValid(int row, int col, int tam1, int tam2) {
	return (row >= 0 && row < tam1 && col >= 0 && col < tam2);
}

bool isFree(char m[MAX_SIZE][MAX_SIZE], int row, int col) {
	return (m[row][col] == ' ' || m[row][col] == '_');
}

bool isSolution(char m[MAX_SIZE][MAX_SIZE], int row, int col, int endRow, int endCol) {
	return (row == endRow && col == endCol);
}

void findPath(char m[MAX_SIZE][MAX_SIZE], int tam1, int tam2, int startRow, int startCol, int endRow, int endCol) {
	queue<pair<int, int>> q;
	q.push({ startRow, startCol });

	int dr[] = { -1, 1, 0, 0 }; // Up, Down, Left, Right
	int dc[] = { 0, 0, -1, 1 };

	while (!q.empty()) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();

		// Check if we reached the end
		if (isSolution(m, row, col, endRow, endCol)) {
			m[row][col] = 'E'; // Mark as part of the path
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
	if (m[endRow][endCol] == 'E') {
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


	/*void imprimir(int m[10][10], int x, int y)
	{


		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (i == x and j == y)
				{
					colorir(10);     /// colorir faz com que a escrita a seguir seja com a cor número 10
					cout << char(2); /// impressão do personagem.
					colorir(7);      /// retorna a cor original após o fim da escrita
				}
				else
				{
					switch (m[i][j])
					{
					case 0:
						cout << " "; /// impressão do espaço vazio
						break;

					case 1:
						colorir(14);
						// cout<<char(178); ///impressão da parede
						cout << char(219); /// impressão da parede
						colorir(7);
						break;

					case 2:
						colorir(12);
						cout << char(219); /// impressão da caixa
						colorir(7);
						break;
					case 3:
						colorir(9);
						cout << char(4); /// impressão do destino da caixa
						colorir(7);
						break;
					case 4:
						colorir(11);
						cout << char(219); /// impressão da caixa no destino
						colorir(7);
						break;
					}
				}

			}
			cout << "\n";
		}
	}
	*/


#endif // HEADER_H_INCLUDED