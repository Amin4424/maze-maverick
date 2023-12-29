#include <iostream>
<<<<<<< HEAD
#include <time.h>

using namespace std;

int **PlateMaker(int row, int col);
void PathMaker(int row, int col, int **&plate);
void PathFinder(int row, int col, int **&plate, int **&already_pos, int sum);

int main()
{
    int **plate;
    int row, col;
    cin >> row >> col;
    plate = PlateMaker(row, col);

    PathMaker(row, col, plate);

    PathFinder(row, col, plate, plate, 0);

    return 0;
=======
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
>>>>>>> main
}

int **PlateMaker(int row, int col)
{
    srand(time(0));
    int **plate = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
    {
        *(plate + i) = (int *)malloc(sizeof(int) * col);
        for (int j = 0; j < col; j++)
        {
            *(*(plate + i) + j) = rand() % 21 - 10;
        }
    }
    return plate;
}

void PathMaker(int row, int col, int **&plate)
{
    int i_pos = 0, j_pos = 0, sum = 0;
    while (i_pos != row - 1 || j_pos != col - 1)
    {
        if (i_pos != row - 1)
        {
            int rnd = rand() % (row - i_pos);
            for (int i = 0; i < rnd; i++)
            {
                int rnd = rand() % 21 - 10;
                while (rnd == 0)
                {
                    rnd = rand() % 21 - 10;
                }

                plate[i_pos][j_pos] = rnd;
                sum += rnd;
                i_pos++;
            }
        }

        if (j_pos != col - 1)
        {
            int rnd = rand() % (col - j_pos);
            for (int i = 0; i < rnd; i++)
            {
                int rnd = rand() % 21 - 10;
                while (rnd == 0)
                {
                    rnd = rand() % 21 - 10;
                }
                plate[i_pos][j_pos] = rnd;
                sum += rnd;
                j_pos++;
            }
        }
    }
    plate[i_pos][j_pos] = sum;
}

bool U(int row, int col, int **&plate, int **&already_pos)
{
    
}

bool D(int row, int col, int **&plate, int **&already_pos)
{

}

bool R(int row, int col, int **&plate, int **&already_pos)
{

}

bool L(int row, int col, int **&plate, int **&already_pos)
{

}

void PathFinder(int row, int col, int **&plate, int **&already_pos, int sum)
{
    // creating temp_plate

    /*int**temp_plate = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
    {
        *(temp_plate + i) = (int *)malloc(sizeof(int) * col);
        for (int j = 0; j < col; j++)
        {
            temp_plate[i][j] = rand() % 21 - 10;
        }
    }*/

    if (*already_pos == (*(plate + row - 1) + col - 1))
    {
        if (sum == plate[row - 1][col - 1])
        {
            /* Finded */
        }
        else
        {
            return;
        }
    }
    else if (U && !D && !R && !L)
    {
        /* code */
    }
    else if (!U && D && !R && !L)
    {
        /* code */
    }
    else if (!U && !D && R && !L)
    {
        /* code */
    }
    else if (!U && !D && !R && L)
    {
        /* code */
    }
    
}