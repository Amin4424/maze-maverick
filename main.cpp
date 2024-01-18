#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <algorithm>
#include <string>
using namespace std;

void CreateMap();
void CreateMapEasy();
void CreateMapHard();
void coutmap(int row, int col, int **map);
void CreateMapHard();
void Playground();
void SolveMaze();
void History();
void Leaderboard();
void monitor(int row, int col, int **map);
void monitor(int row, int col, int **path, int **map);
void StartProgram();
int **PlateMaker(int row, int col);
void PathMaker(int row, int col, int sum, int min, int max, int **&plate);
void PathMaker2(int row, int col, int len, int min, int max, int **&plate);
void SolveMaze();
void SolveMaze_1();
void ShowPath(int row, int col, int **&map, int **&maze);
bool solveMaze(int **maze, int rows, int cols, int startX, int startY, int endRow, int endCol, int pathSum, int &shortestPath, int **&ans);
void SolveMaze(int row, int col, int **&map, int **&ans);
void PlateDeleter(int row, int **&plate);
void Blocker(int Bmin, int Bmax, int row, int col, int **&maze);

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
            cout << "\033[2J\033[1;1H";
            CreateMap();
            break;

        case '2':
            cout << "\033[2J\033[1;1H";
            // Playground();
            break;

        case '3':
            cout << "\033[2J\033[1;1H";
            SolveMaze();
            break;

        case '4':
            cout << "\033[2J\033[1;1H";
            // History();
            break;
        case '5':
            cout << "\033[2J\033[1;1H";
            Leaderboard();
            break;

        case '6':
            cout << "\033[2J\033[1;1H";
            cout << "Exiting the program...";
            exit(0);
            break;

        default:
            cout << "\033[2J\033[1;1H";
            cout << "Please press a valid key" << endl;
            break;
        }
    }
}

void CreateMap()
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
            cout << "\033[2J\033[1;1H";
            CreateMapEasy();
            break;

        case '2':
            cout << "\033[2J\033[1;1H";
            CreateMapHard();
            break;

        case '3':
            cout << "\033[2J\033[1;1H";
            return;

        default:
            cout << "\033[2J\033[1;1H";
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

    PathMaker(row, col, 0, -3, 3, map);

    Blocker(2, 5, row, col, map);

    ofstream file("Maps/" + mapname + ".txt");
    file << row << endl
         << col << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            file << map[i][j] << ' ';
        }
        file << "\n";
    }

    monitor(row, col, map);
    PlateDeleter(row, map);
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
    PathMaker2(row, col, len, min, max, map);
    Blocker(minB, maxB, row, col, map);

    ofstream file("Maps/" + mapname + ".txt");
    file << row << endl
         << col << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            file << map[i][j] << ' ';
        }
        file << "\n";
    }

    monitor(row, col, map);
    // PlateDeleter(row, map);
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

void History()
{
}

void Leaderboard()
{
}

// Map Section
void monitor(int row, int col, int **map)
{
    int MaxLength = to_string(map[0][0]).size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (to_string(map[i][j]).size() > MaxLength)
                MaxLength = to_string(map[i][j]).size();
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "+";
            for (int k = 0; k < MaxLength + 2; k++)
            {
                cout << "-";
            }
        }
        cout << "+" << endl;

        for (int j = 0; j < col; j++)
        {
            int lengthofnumber = to_string(map[i][j]).size();
            cout << '|';
            for (int k = 1; k <= (MaxLength - lengthofnumber) + 2; k += 2)
            {
                cout << ' ';
            }
            cout << map[i][j];
            for (int k = 1; k <= (MaxLength - lengthofnumber) + 1; k += 2)
            {
                cout << ' ';
            }
        }

        cout << '|' << endl;
    }

    for (int j = 0; j < col; j++)
    {
        cout << "+";
        for (int k = 0; k < MaxLength + 2; k++)
        {
            cout << "-";
        }
    }
    cout << "+" << endl;
}

void monitor(int row, int col, int **path, int **map)
{
    int temp;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
            if ((map[i][j] == path[i][j]) && (map[i][j] != 0))
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << map[i][j];
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                cout << map[i][j];
            }

            cout << ' ';
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

void PathMaker(int row, int col, int sum, int min, int max, int **&plate)
{
    int i_pos = 0, j_pos = 0, range;
    range = max - min + 1;
    while (i_pos < row - 1 || j_pos < col - 1)
    {
        if (i_pos < row - 1)
        {
            int rnd1 = rand() % ((row - i_pos) / 2 + 1);
            for (int i = 0; i < rnd1; i++)
            {
                int rnd = rand() % range + min;
                while (rnd == 0)
                {
                    rnd = rand() % range + min;
                }

                plate[i_pos][j_pos] = rnd;
                sum += rnd;
                i_pos++;
            }
        }

        if (j_pos < col - 1)
        {
            int rnd1 = rand() % ((col - j_pos) / 2 + 1);
            for (int i = 0; i < rnd1; i++)
            {
                int rnd = rand() % range + min;
                while (rnd == 0)
                {
                    rnd = rand() % range + min;
                }
                plate[i_pos][j_pos] = rnd;
                sum += rnd;
                j_pos++;
            }
        }
    }
    plate[i_pos][j_pos] = sum;
}

void PathMaker2(int row, int col, int len, int min, int max, int **&map)
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
                    PathMaker(temprow, tempcol, sum, min, max, tempmap);
                    for (int x = 0; x < temprow; x++)
                    {
                        for (int y = 0; y < tempcol; y++)
                        {
                            map[x + i_pos][y + j_pos] = tempmap[x][y];
                        }
                    }
                    // PlateDeleter(row, tempmap);
                    return;
                }
            }
            j_pos++;
            i_pos++;
        }
    }
}

void SolveMaze()
{
    char input = 0;
    while (input != '3')
    {
        cout << "1. Enter the name of map\n   (The file has to exist in Maps/ directory)\n"
             << endl;
        cout << "2. Quit" << endl;
        input = _getch();
        switch (input)
        {
        case '1':
            // system("clear");
            SolveMaze_1();
            break;
        case '2':
            // system("clear");
            return;

        default:
            // system("clear");
            cout << "Please press a valid key" << endl;
            break;
        }
    }
}

void SolveMaze_1()
{
    cout << "Please enter the name of txt file:\n(example: test.txt)\n";
    string name;
    cin >> name;
    ifstream file("Maps/" + name);
    while (!file)
    {
        cout << "Something went wrong!\nPlease try again:\n";
        cin >> name;
        file.open("Maps/" + name);
    }
    int row, col;
    file >> row >> col;
    int **map = PlateMaker(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            file >> map[i][j];
        }
    }

    file.close();
    int **ans = PlateMaker(row, col);

    SolveMaze(row, col, map, ans);
    // ShowPath(row, col, map, ans);
    PlateDeleter(row, ans);
}

void ShowPath(int row, int col, int **&map, int **&ans)
{
    int **path = PlateMaker(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((map[i][j] != ans[i][j]) || ((i == row - 1) && (j == col - 1)))
            {
                path[i][j] = map[i][j];
            }
            else
            {
                path[i][j] = 0;
            }
        }
    }
    monitor(row, col, path, map);
    // PlateDeleter(row, path);
}

void SolveMaze(int row, int col, int **&maze, int **&ans)
{
    int startX = 0, startY = 0;
    int endRow = row - 1, endCol = col - 1;
    int pathSum = 0;
    int shortestPath = INT_MAX;
    int **maze_keeper = PlateMaker(row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            maze_keeper[i][j] = maze[i][j];
        }
    }

    if (solveMaze(maze, row, col, startX, startY, endRow, endCol, pathSum, shortestPath, ans))
    {
        ShowPath(row, col, maze_keeper, ans);
    }
    else
    {
        cout << "No path found" << endl;
    }

    PlateDeleter(row, maze);
}
bool solveMaze(int **maze, int rows, int cols, int startX, int startY, int endRow, int endCol, int pathSum, int &shortestPath, int **&ans)
{
    int **new_maze = PlateMaker(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            new_maze[i][j] = maze[i][j];
        }
    }

    if (startX < 0 || startX >= rows || startY < 0 || startY >= cols || maze[startX][startY] == 0)
    {

        PlateDeleter(rows, new_maze);

        return false;
    }

    if (startX == endRow && startY == endCol)
    {
        if (pathSum == maze[endRow][endCol])
        {
            if (pathSum < shortestPath)
            {
                shortestPath = pathSum;
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        ans[i][j] = maze[i][j];
                    }
                }
            }
            return true;
        }
        else
        {

            PlateDeleter(rows, new_maze);

            return false;
        }
    }

    pathSum += maze[startX][startY];
    new_maze[startX][startY] = 0;

    if (solveMaze(new_maze, rows, cols, startX + 1, startY, endRow, endCol, pathSum, shortestPath, ans) ||
        solveMaze(new_maze, rows, cols, startX - 1, startY, endRow, endCol, pathSum, shortestPath, ans) ||
        solveMaze(new_maze, rows, cols, startX, startY + 1, endRow, endCol, pathSum, shortestPath, ans) ||
        solveMaze(new_maze, rows, cols, startX, startY - 1, endRow, endCol, pathSum, shortestPath, ans))
    {
        return true;
    }

    PlateDeleter(rows, new_maze);

    return false;
}

void PlateDeleter(int row, int **&plate)
{
    for (int i = 0; i < row; i++)
    {
        delete plate[i];
    }
    delete plate;
}

void Blocker(int Bmin, int Bmax, int row, int col, int **&maze)
{
    int diff = Bmax - Bmin + 1;
    int ZB = rand() % diff + Bmin;
    int min = INT_MAX;
    int max = INT_MIN;
    vector<int *> zeros;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((i == row - 1) && (j == col - 1))
            {
                continue;
            }
            else if (maze[i][j] == 0)
            {
                zeros.push_back(&maze[i][j]);
            }
            else
            {
                if (maze[i][j] > max)
                {
                    max = maze[i][j];
                }

                if (maze[i][j] < min)
                {
                    min = maze[i][j];
                }
            }
        }
    }
    while (zeros.size() > ZB)
    {
        int ind = rand() % (zeros.size() + 1);
        int rnd = rand() % (max - min + 1) + min;
        while (rnd == 0)
        {
            rnd = rand() % (max - min + 1) + min;
        }
        *(zeros[ind]) = rnd;
        zeros[ind] = zeros[zeros.size() - 1];
        zeros.pop_back();
    }
}