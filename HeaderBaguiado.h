#ifndef ROTINAS_H_INCLUDED
#define ROTINAS_H_INCLUDED

#include <iostream>
#include <windows.h> //cursor
#include <conio.h>   //_getch
#include <fstream>   //arquivo
#include <stdlib.h>  //random
#include <thread>	//sleep
#include <atomic>  

using namespace std;

struct MAPA
{
    const char* arquivo;
    int posicaox, posicaoy;

    void carregaMAPA(int ag1[10][7], int ag8[10][8], int ag13[10][8], int& x, int& y)
    {
        ifstream stream;
        stream.open(arquivo);

        if (stream.is_open())
        {
            stream >> posicaox;
            stream >> posicaoy;
            x = posicaox;
            y = posicaoy;

            if (strcmp(arquivo, "AG1.txt") == 0)
            {
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        stream >> ag1[i][j];
                    }
                }
            }
            else if (strcmp(arquivo, "AG8.txt") == 0)
            {
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        stream >> ag8[i][j];
                    }
                }
            }
            else if (strcmp(arquivo, "AG13.txt") == 0)
            {
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        stream >> ag13[i][j];
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

void initializeMap(int m[10][10]) {
    for (int i = 0; i < 10; i++) { // inicializa matriz com 0
        for (int j = 0; j < 10; j++) {
            m[i][j] = 0;
        }
    }
}


void menu(int m[10][10], int& x, int& y, bool& jogando);

/*
0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/



/*void posicaoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}*/ // n sei se devo usar isso




void mostrarCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void colorir(int cor)
{

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(out, cor);
}

// verifica vitória
bool vitoria(int m[10][10])
{
    for (int i = 0; i < 10; i++) // verifica se todas as caixas estão nos destinos
    {
        for (int j = 0; j < 10; j++)
        {
            if (m[i][j] == 3) // enquanto o destino das caixas existir (não for preenchido), o jogo não concede a vitória.
            {
                return false;
            }
        }
    }
    return true;
}





/// se algum dos símbolos não aparecer (ficar com ?, tente substituir a fonte para Fontes de Varredura em propriedades do console -> fonte
void imprimir(int m[10][10], int x, int y)
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
} // fim imprime()

// Selecionar o mapa deveria chamar uma função que carrega um mapa escolhido
// de um arquivo para matriz m
void selecionar_mapa(int m[10][10], int& x, int& y)
{
    char tecla;
    bool jogando;
    int selecionar;
    int n_itens = 1;

    cout << "\nSELECIONE: \n1 - Alberto Garcia 1\n2 - Alberto Garcia 8\n3 - Alberto Garcia 13\n4 - Aleatório";
    cin >> selecionar;
    if (selecionar == 4)
    {
        //selecionar = rand() / n_itens + 1; // gera um selecionar válido aleatório
        selecionar = rand() % 3 + 1;
    }
    switch (selecionar)
    {
    case 1:
    {
        system("cls");
        int ag1[10][7];
        int ag8[10][8];
        int ag13[10][8];
        MAPA mapa;
        mapa.arquivo = "AG1.txt";
        mapa.carregaMAPA(ag1, ag8, ag13, x, y);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                m[i][j] = ag1[i][j];
            }
        }
    }

    break;
    case 2:
    {
        system("cls");
        int ag1[10][7];
        int ag8[10][8];
        int ag13[10][8];
        MAPA mapa;
        mapa.arquivo = "AG8.txt";
        mapa.carregaMAPA(ag1, ag8, ag13, x, y);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                m[i][j] = ag8[i][j];
            }
        }
    }
    break;
    case 3:
    {
        system("cls");
        int ag1[10][7];
        int ag8[10][8];
        int ag13[10][8];
        MAPA mapa;
        mapa.arquivo = "AG13.txt";
        mapa.carregaMAPA(ag1, ag8, ag13, x, y);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                m[i][j] = ag13[i][j];
            }
        }
    }
    break;
    case 4:
    {
        // Generate a random number between 1 and 3
        int randomCase = rand() % 3 + 1;

        if (randomCase == 1)
        {
            system("cls");
            int ag1[10][7];
            int ag8[10][8];
            int ag13[10][8];
            MAPA mapa;
            mapa.arquivo = "AG1.txt";
            mapa.carregaMAPA(ag1, ag8, ag13, x, y);

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    m[i][j] = ag1[i][j];
                }
            }
        }
        else if (randomCase == 2)
        {
            system("cls");
            int ag1[10][7];
            int ag8[10][8];
            int ag13[10][8];
            MAPA mapa;
            mapa.arquivo = "AG8.txt";
            mapa.carregaMAPA(ag1, ag8, ag13, x, y);

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    m[i][j] = ag8[i][j];
                }
            }
        }
        else if (randomCase == 3)
        {
            system("cls");
            int ag1[10][7];
            int ag8[10][8];
            int ag13[10][8];
            MAPA mapa;
            mapa.arquivo = "AG13.txt";
            mapa.carregaMAPA(ag1, ag8, ag13, x, y);

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    m[i][j] = ag13[i][j];
                }
            }
        }
    }
    break;

    // ...


    // fim switch
    system("cls");
    } // fim selecionar
}

int contador(int m[10][10], bool& jogando) // conta o número de passos
{

    ofstream aqpassos; // cria o stream ofstream para gravação
    aqpassos.open("passos.txt"); // abre o arquivo passos.txt
    short int contaPassos = 0; // conta o número de passos
    short int x = 0, y = 0; // posição inicial do personagem
    char tecla; // tecla pressionada
    while (jogando)
    {
        if (_kbhit()) { // se alguma tecla for pressionada
            tecla = _getch(); // pega a tecla pressionada
            if (tecla == 77 || tecla == 75 || tecla == 80 || tecla == 72) { // se a tecla for uma das setas
                contaPassos++; // conta o número de passos
                aqpassos << contaPassos << endl; // grava o número de passos no arquivo passos.txt


            }
        }
    }
    aqpassos.close(); // fecha o arquivo passos.txt
    return contaPassos; // retorna o número de passos

}

void sokoban(int m[10][10], int& x, int& y, bool& jogando) // função principal do header
{

    while (!vitoria(m) && jogando)
    {
        imprimir(m, x, y); // imprime o mapa
        /*posicaoxy(0, 0);
        movimentar(m, x, y); // movimenta o personagem
        */
        contador(m, jogando); // conta o número de passos e escreve no "passos.txt"
    }

    if (vitoria(m))
    {
        jogando = false;
        system("cls");
        cout << "\nVocê venceu!\nAperte qualquer tecla para retornar ao menu.\n";
        char tecla = _getch();
        system("cls");
    }
    else
    {
        // Handle the case when the player chooses to exit the game before winning
        jogando = true;
        system("cls");
        cout << "\nVocê saiu do jogo.\nAperte qualquer tecla para retornar ao menu.\n";
        char tecla = _getch();
        system("cls");
    }

    menu(m, x, y, jogando); // Go back to the main menu
}

void sobre(int m[10][10], int& x, int& y, bool& jogando)
{
    cout << "\t LABIRINTH PATH FINDER & CONSTRUCTOR\n";
    cout << "Versão 0.1\n";
    cout << "Aluno: Carlos Augusto Mallmann Serena\n";
    cout << "Professor: Marcos Carrard\n";
    cout << "Como utilizar o path finder: \n";
    cout << "1 - Insira a posição de inicio e fim utilizando coordenadas.\n";
    cout << "2 - Apos isso o programa tentara (se possivel) achar um caminho e completar o labirinto\n";
    cout << "3 - Para voltar ao menu use a tecla ESC\n";
    cout << "Para sair desse menu aperte qualquer tecla\n";
    system("pause");
    char tecla = _getch();
    system("cls");
    menu(m, x, y, jogando);
}

void menu(int m[10][10], int& x, int& y, bool& jogando)
{

    int selecionar;
    system("cls");
    cout << "\tLABIRINTH PATH FINDER & CONSTRUCTOR\n\nSELECIONE: \n\n1 - novo labirinto\n2 - achar caminho de um labirinto\n3 - sobre\n4 - sair\n";
    cin >> selecionar;
    switch (selecionar)
    {
    case 1:
        jogando = true;
        system("cls");
        selecionar_mapa(m, x, y);
        sokoban(m, x, y, jogando);
        break;
    case 2:
        if (jogando)
        {
            system("cls");
            sokoban(m, x, y, jogando);
        }
        else
        {
            system("cls");
            jogando = true;
            selecionar_mapa(m, x, y);
            sokoban(m, x, y, jogando);
        }

        break;
    case 3:
        system("cls");
        sobre(m, x, y, jogando);
        break;
    case 4:
        exit(0);
        break;
    } // fim switch

    system("cls");
} // fim selecionar



#endif // ROTINAS_H_INCLUDED



