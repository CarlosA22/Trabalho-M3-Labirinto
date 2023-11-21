#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <windows.h> //cursor
#include <conio.h>   //_getch
#include <fstream>   //arquivo
#include <stdlib.h>  //random
#include <thread>	//sleep
#include <atomic>  
#include <string>

using namespace std;

struct MapaCordenadas
{
	int x;
	int y;
	MapaCordenadas(int _x = 0, int _y = 0) { x = _x, y = _y; }
	MapaCordenadas(const MapaCordenadas& coord) { x = coord.x; y = coord.y; }
};

MapaCordenadas startingPoint(1, 0);
MapaCordenadas endingPoint(7, 8);

void InicializarMapa(int m[10][10]) {
	for (int i = 0; i < 10; i++) { // inicializa matriz com 0
		for (int j = 0; j < 10; j++) {
			m[i][j] = 0;
		}
	}
}

void colorir(int cor)
{

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, cor);
}

void criarMapa()
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

void imprimirMapa()
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



void descobrirCaminhoDoLabirinto()
{
	ifstream lab01;
	lab01.open("lab01.txt");
	string linhaTamanho;
	int tam1 = 0, tam2 = 0;
	char parede = '#', caminho = '_';

	if (lab01.is_open)
	{
		//getline(lab01, linhaTamanho, '\n');
		lab01 >> tam1;
		//getline(lab01, linhaTamanho, '\n');
		lab01 >> tam2;
		//cout<< tam1 << tam2 << endl;


		char** m = new char* [tam1];
		for (int i = 0; i < tam1; ++i) {
			m[i] = new char[tam2];
		}

		for (int i = 0; i < tam1; i++)
		{
			for (int j = 0; j < tam2; j++) // apos cada linha tem uma quebra de linha
			{
				m[i][j] = lab01.get();
			}
		}
	}
	for (int i = 0; i < tam1; ++i) {
		delete[] m[i];
	}
	delete[] m;
	lab01.close();



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