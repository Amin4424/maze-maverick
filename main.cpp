#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>

using namespace std;

void CreateMap();
void CreateMapEasy();
void coutmap(int row, int col, int **map);
void CreateMapHard();
void Playground();
void SolveMaze();
void History();
void Leaderboard();
void monitor(int row, int col, int **map);
void StartProgram();
int **PlateMaker(int row, int col);
void PathMaker(int row, int col, int **&plate);

int main()
{
    StartProgram();

    // int **plate;
    // int row, col;
    // cin >> row >> col;
    // plate = PlateMaker(row, col);

    // PathMaker(row, col, plate);

    // PathFinder(row, col, plate, plate, 0);

    return 0;
}

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
            // system("clear");
            CreateMap();
            break;

        case '2':
            // system("clear");
            // Playground();
            break;

        case '3':
            // system("clear");
            // SolveMaze();
            break;

        case '4':
            // system("clear");
            // History();
            break;
        case '5':
            // system("clear");
            Leaderboard();
            break;

        case '6':
            system("clear");
            cout << "Exiting the program...";
            exit(0);
            break;

        default:
            // system("clear");
            cout << "Please press a valid key" << endl;
            break;
        }
    }
}

void CreateMap()
{
    char input=0;
    cout << "1. Easy" << endl;
    cout << "2. Hard" << endl;
    cout << "3. Quit" << endl;
    while (input != '3')
    {
        input = getchar();
        switch (input)
        {
        case '1':
            // system("clear");
            CreateMapEasy();
            break;

        case '2':
            // system("clear");
            CreateMapEasy();
            break;

        case '3':
            // system("clear");
            return;

        default:
            // system("clear");
            cout << "Please press a valid key" << endl;
            break;
        }
    }
}

void CreateMapEasy()
{
    int row, col;
    do
    {
        cout << "Enter the number of rows:\n";
        cin >> row;
    } while (row <= 0);

    do
    {
        cout << "Enter the number of columns:\n";
        cin >> col;
    } while (col <= 0);

    string mapname;
    cout << "Enter your map name:\n";
    cin >> mapname;

    int **map = PlateMaker(row, col);

    PathMaker(row, col, map);

    monitor(row, col, map);
}

void coutmap(int row, int col, int **map)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << *(*(map + i) + j) << ' ';
        }
        cout << endl;
    }
}

void Playground()
{
}

void SolveMaze()
{
}

void History()
{
}

void Leaderboard()
{
}

// Map Section
void monitor(int row, int col, int **map)
{
    int temp;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "+-----";
        }
        cout << "+" << endl;
        for (int j = 0; j < col; j++)
        {
            cout << "| ";
            if (map[i][j] / 10 == 0)
            {
                if (map[i][j] >= 0)
                    cout << "  ";
                else
                    cout << ' ';
            }
            else if (map[i][j] / 10 > 0)
            cout << ' ';
            cout << map[i][j] << ' ';
        }
        cout << '|' << endl;
    }
    for (int j = 0; j < col; j++)
    {
        cout << "+-----";
    }
    cout << "+" << endl;
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
            *(*(plate + i) + j) = 0;
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
            int rnd = rand() % ((row - i_pos) / 2 + 1);
            for (int i = 0; i < rnd; i++)
            {
                int rnd = rand() % 6 - 3;
                while (rnd == 0)
                {
                    rnd = rand() % 6 - 3;
                }

                plate[i_pos][j_pos] = rnd;
                sum += rnd;
                i_pos++;
            }
        }

        if (j_pos != col - 1)
        {
            int rnd = rand() % ((col - j_pos) / 2 + 1);
            for (int i = 0; i < rnd; i++)
            {
                int rnd = rand() % 6 - 3;
                while (rnd == 0)
                {
                    rnd = rand() % 6 - 3;
                }
                plate[i_pos][j_pos] = rnd;
                sum += rnd;
                j_pos++;
            }
        }
    }
    plate[i_pos][j_pos] = sum;
}