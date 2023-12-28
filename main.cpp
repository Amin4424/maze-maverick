
#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

void CreateMap();
void Playground();
void SolveMaze();
void History();
void Leaderboard();
void map(int, int);
void StartProgram();

int main()
{
    StartProgram();
}

    // Menu
void StartProgram()
{
    while (1)
    {
        cout << "1. Create a New Map" << endl;
        cout << "2. Playground" << endl;
        cout << "3. Solve a Maze" << endl;
        cout << "4. History" << endl;
        cout << "5. Leaderboard" << endl;
        cout << "6. Exit" << endl;

        char input = _getch();
        switch (input)
        {
        case '1':
            system("cls");
            CreateMap();
            break;

        case '2':
            system("cls");
            Playground();
            break;

        case '3':
            system("cls");
            SolveMaze();
            break;

        case '4':
            system("cls");
            History();
            break;
        case '5':
            system("cls");
            Leaderboard();
            break;

        case '6':
            system("cls");
            cout << "Exiting the program...";
            exit(0);
            break;

        default:
            system("cls");
            cout << "Please press a valid key" << endl;
            break;
        }
    }
}
// Map Section
void map(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "+----";
        }
        cout << "+" << endl;
        for (int j = 0; j < col; j++)
        {
            cout << "| 01 ";
        }
        cout << "|" << endl;
    }
    for (int j = 0; j < col; j++)
    {
        cout << "+----";
    }
    cout << "+" << endl;
}