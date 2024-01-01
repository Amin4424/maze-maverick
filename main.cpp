#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

void CreateMapSection();
void CreateMapEasy();
void CreateMapHard();
void coutmap(int row, int col, int **map);
void Playground();
void SolveMazeSection();
void SolvingSystemMaps();
void SolvingUserMap();
void History();
void Leaderboard();
void monitor(int row, int col, int **map);
void StartProgram();
int **PlateMaker(int row, int col);
void PathMaker(int row, int col, int sum, int **&plate);
void PathMaker(int row, int col, int len, int min, int max, int **&plate);

int main()
{
    StartProgram();
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
            CreateMapSection();
            break;

        case '2':
            // system("clear");
            // Playground();
            break;

        case '3':
            // system("clear");
            SolveMazeSection();
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
            // system("clear");
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

void CreateMapSection()
{
    char input = 0;
    while (input != '3')
    {
        cout << "1. Easy" << endl;
        cout << "2. Hard" << endl;
        cout << "3. Quit" << endl;
        input = _getch();
        switch (input)
        {
        case '1':
            // system("clear");
            CreateMapEasy();
            break;

        case '2':
            // system("clear");
            CreateMapHard();
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

    PathMaker(row, col, 0, map);

    ofstream file("Maps/" + mapname + ".txt");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            file << map[i][j] << ' ';
        }
        file << "\n";
    }

    monitor(row, col, map);
}

void CreateMapHard()
{
    int row, col, len, min, max, minB, maxB;
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

    do
    {
        cout << "Enter the lenght of path:\n";
        cin >> len;
        if ((len < (row + col - 2)) || (len >= (row * col)) || ((len - (row + col - 2)) % 2 != 0) || ((row % 2 == 0) && (col % 2 == 0) && (len = row * col - 1)))
            cout << "Invalid path!\n";
    } while ((len < (row + col - 2)) || (len >= (row * col)) || ((len - (row + col - 2)) % 2 != 0) || ((row % 2 == 0) && (col % 2 == 0) && (len = row * col - 1)));

    cout << "Enter the minimum amount of each block:\n";
    cin >> min;

    do
    {
        cout << "Enter the maximum amount of each block:\n";
        cin >> max;
    } while (max < min);

    do
    {
        cout << "Enter the minimum number of blocked blocks:\n";
        cin >> minB;
    } while (minB > (row * col - len - 1));

    do
    {
        cout << "Enter the maximum number of blocked blocks:\n";
        cin >> maxB;
    } while ((maxB > (row * col - len - 1)) || maxB < minB);

    string mapname;
    cout << "Enter your map name:\n";
    cin >> mapname;

    int **map = PlateMaker(row, col);
    PathMaker(row, col, len, min, max, map);

    ofstream file("Maps/" + mapname + ".txt");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            file << map[i][j] << ' ';
        }
        file << "\n";
    }

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

void SolveMazeSection()
{
    char input;
    while (input != '3')
    {
        cout << "Please press your choice : " << endl;
        cout << "1. Choosing from maps that has been made. " << endl;
        cout << "2. Reading a map. " << endl;
        cout << "3. Quit this section." << endl;
        input = _getch();
        switch (input)
        {
        case '1':
            // system("clear");
            // SolvingSystemMaps();
            break;

        case '2':
            // system("clear");
            SolvingUserMap();
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

void PathMaker(int row, int col, int sum, int **&plate)
{
    int i_pos = 0, j_pos = 0;
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

void PathMaker(int row, int col, int len, int min, int max, int **&map)
{
    // it works only on even_rowed maps for now
    int i_pos = 0, j_pos = 0, sum = 0, range, diff;
    range = max - min + 1;
    diff = 0 - min;
    while (1)
    {
        if (i_pos % 2 == 0)
        {
            for (int i = 0; i < col; i++)
            {
                int rnd = rand() % range - diff;
                while (rnd == 0)
                {
                    rnd = rand() % range - diff;
                }
                map[i_pos][j_pos] = rnd;
                sum += rnd;
                j_pos++;
                len--;
                if ((j_pos == col - 1) && (i_pos == row - 1))
                {
                    map[i_pos][j_pos] = sum;
                    return;
                }
            }
            j_pos--;
            i_pos++;
        }

        if (i_pos % 2 == 1)
        {
            for (int i = 0; i < col; i++)
            {
                int rnd = rand() % range - diff;
                while (rnd == 0)
                {
                    rnd = rand() % range - diff;
                }
                map[i_pos][j_pos] = rnd;
                sum += rnd;
                j_pos--;
                len--;
                if (((row - i_pos - 1) + (col - j_pos - 1) - 2) == len)
                {
                    j_pos++;
                    i_pos++;
                    int temprow = row - i_pos;
                    int tempcol = col - j_pos;
                    int **tempmap = PlateMaker(temprow, tempcol);
                    PathMaker(temprow, tempcol, sum, tempmap);
                    for (int x = 0; x < temprow; x++)
                    {
                        for (int y = 0; y < tempcol; y++)
                        {
                            map[x + i_pos][y + j_pos] = tempmap[x][y];
                        }
                    }
                    delete tempmap;
                    return;
                }
            }
            j_pos++;
            i_pos++;
        }
    }
}

void SolvingUserMapSection()
{
    char input;
    while (input != 'y')
    {
        int row, col;
        cout << "Enter number of rows and columns for the map : ";
        cin >> row >> col;
        int map[row][col];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << "Enter a number for a" << i << j << " element : \n";
                cin >> map[i][j];
            }
        }
        cout << "Is this what you want to be solved? : \n";
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
        cout<<"1. Press (y) for yes"<<endl;
        cout<<"2. Press (n) for no"<<endl;
        input = _getch();
        switch (input)
        {
        case 'y':
            // system("clear");
            break;

        case 'n':
            // system("clear");
            continue;;

        default:
            // system("clear");
            cout << "Please press a valid key" << endl;
            continue;;
        }


    }
}