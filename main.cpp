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
#include <chrono>
#include <filesystem>
#include <sstream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"

using namespace std;
namespace fs = filesystem;

void StartProgram();
void CreateMapSection();
void CreateMapEasy();
void CreateMapHard();
void PlaygroundSection();
void SolveMazeSection();
bool bruteForce(int **maze, int rows, int cols, int startX, int startY, int endRow, int endCol, int pathSum, int &shortestPath, int **&ans);
void History();
void Leaderboard();
void monitor(int row, int col, int **map);
void monitor(int row, int col, int **path, int **map);
int **PlateMaker(int row, int col);
void PathMaker(int row, int col, int sum, int min, int max, int **&plate);
void PathMakerHard(int row, int col, int len, int min, int max, int **&plate);
void SolveMaze();
void ShowPath(int row, int col, int **&map, int **&maze);
void PlateDeleter(int row, int **&plate);
void Blocker(int Bmin, int Bmax, int row, int col, int **&maze);
void ColorizeAndMonitor(int row, int col, int **map, int Pos_x, int Pos_y, int pathSum, vector<int> vis_i, vector<int> vis_j);

int main()
{
    system("cls");
    StartProgram();
    return 0;
}

void StartProgram()
{
    while (1)
    {
        cout << BLUE << "1. Create a New Map" << endl;
        cout << RED << "2. PlaygroundSection" << endl;
        cout << GREEN << "3. Solve a Maze" << endl;
        cout << YELLOW << "4. History" << endl;
        cout << CYAN << "5. Leaderboard" << endl;
        cout << MAGENTA << "6. Exit" << endl;
        cout << RESET;

        char input = _getch();
        switch (input)
        {
        case '1':
            system("cls");
            CreateMapSection();
            break;

        case '2':
            system("cls");
            PlaygroundSection();
            break;

        case '3':
            system("cls");
            SolveMazeSection();
            break;

        case '4':
            system("cls");
            // History();
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
            system("cls");
            CreateMapEasy();
            break;

        case '2':
            system("cls");
            CreateMapHard();
            break;

        case '3':
            system("cls");
            return;

        default:
            system("cls");
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
    PathMakerHard(row, col, len, min, max, map);
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

void PlaygroundSection()
{
    cout << "Choose your option: \n";
    cout << "1. Choosing a map from pre-made maps \n";
    cout << "2. Reading a map\n";
    cout << "3. Quit\n";
    char option;
    option = _getch();

    switch (option)
    {
    case '1':
    {
        system("cls");
        string path = "Maps";
        cout << "Choose the map:" << endl;
        for (const auto &entry : fs::directory_iterator(path))
        {
            cout << entry.path().filename() << endl;
        }
        string name;
        cin >> name;
        ifstream file("Maps/" + name);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file" << endl;
            break;
        }

        int row, col;
        file >> row >> col;
        int MaxLengthOfIndex = 0;
        int **map = new int *[row];
        for (int i = 0; i < row; ++i)
        {
            map[i] = new int[col];
            for (int j = 0; j < col; ++j)
            {

                if (!(file >> map[i][j]))
                {
                    system("cls");
                    cout << "Error: Unable to read from file" << endl;
                    for (int k = 0; k < i; ++k)
                        delete[] map[k];

                    delete[] map;
                    file.close();
                    return;
                }
            }
        }
        system("cls");
        string username;
        cout << "Enter a username please:" << endl;
        cin >> username;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (to_string(map[i][j]).size() > MaxLengthOfIndex)
                {
                    MaxLengthOfIndex = to_string(map[i][j]).size();
                }
            }
        }
        int CheckIfVisited[row][col];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                CheckIfVisited[i][j] = map[i][j];
            }
        }
        file.close();
        bool validmove1 = false, validmove2 = false, validmove3 = false, validmove4 = false;
        bool win = false, lose = false;
        int I = 0, J = 0, Sum = 0;
        vector<int> vis_i;
        vector<int> vis_j;
        vis_i.push_back(I);
        vis_j.push_back(J);
        Sum += map[I][J];
        CheckIfVisited[I][J] = 0;
        char direction;
        string input;
        getline(cin, input);
        system("cls");
        using namespace std::chrono;
        auto start = high_resolution_clock::now();
        ColorizeAndMonitor(row, col, map, I, J, Sum, vis_i, vis_j);
        while (1)
        {

            if (Sum == map[row - 1][col - 1] && I == row - 1 && J == col - 1)
            {
                win = true;
                break;
            }
            if (I == row - 1 && J == col - 1 && Sum != map[row - 1][col - 1] || (validmove1 && validmove2 && validmove3 & validmove4))
            {
                lose = true;
                break;
            }
            direction = _getch();
            switch (direction)
            {
            case 'w':
                system("cls");
                if (I - 1 >= 0 && map[I - 1][J] != 0 && CheckIfVisited[I - 1][J] != 0)
                {
                    validmove1 = false;
                    I -= 1;
                    CheckIfVisited[I][J] = 0;
                    if (map[I][J] != map[row - 1][col - 1])
                        Sum += map[I][J];
                    vis_i.push_back(I);
                    vis_j.push_back(J);
                }
                else
                    validmove1 = true;
                ColorizeAndMonitor(row, col, map, I, J, Sum, vis_i, vis_j);
                continue;
            case 's':
                system("cls");
                if (I + 1 < row && map[I + 1][J] != 0 && CheckIfVisited[I + 1][J] != 0)
                {
                    validmove2 = false;
                    I += 1;
                    CheckIfVisited[I][J] = 0;
                    if (map[I][J] != map[row - 1][col - 1])
                        Sum += map[I][J];
                    vis_i.push_back(I);
                    vis_j.push_back(J);
                }
                else
                    validmove2 = true;
                ColorizeAndMonitor(row, col, map, I, J, Sum, vis_i, vis_j);
                continue;
            case 'a':
                system("cls");
                if (J - 1 >= 0 && map[I][J - 1] != 0 && CheckIfVisited[I][J - 1] != 0)
                {
                    validmove3 = false;
                    J -= 1;
                    CheckIfVisited[I][J] = 0;
                    if (map[I][J] != map[row - 1][col - 1])
                        Sum += map[I][J];
                    vis_i.push_back(I);
                    vis_j.push_back(J);
                }
                else
                    validmove3 = true;
                ColorizeAndMonitor(row, col, map, I, J, Sum, vis_i, vis_j);
                continue;
            case 'd':
                system("cls");
                if (J + 1 < col && map[I][J + 1] != 0 && CheckIfVisited[I][J + 1] != 0)
                {
                    validmove4 = false;
                    J += 1;
                    CheckIfVisited[I][J] = 0;
                    if (map[I][J] != map[row - 1][col - 1])
                        Sum += map[I][J];
                    vis_i.push_back(I);
                    vis_j.push_back(J);
                }
                else
                    validmove4 = true;
                ColorizeAndMonitor(row, col, map, I, J, Sum, vis_i, vis_j);
                continue;
            case 'q':
                system("cls");
                return;
            default:
                system("cls");
                cout << RED << "Please press a valid key" << RESET << endl;
                Sleep(1000);
                system("cls");
                ColorizeAndMonitor(row, col, map, I, J, Sum, vis_i, vis_j);
                continue;
            }
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(end - start);
        if (win)
        {
            string LastWinDay, LastWinMonth, LastWinDate, LastWinTime, LastWinYear;
            bool FindLastWin = true;
            int TotalGames = 0, WonGames = 0, AllDurationSpent = 0;
            auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::string timeString = std::ctime(&currentTime);
            ifstream inFile("SaveUserData/UserData.txt");
            vector<string> existingData;
            string Line;
            while (getline(inFile, Line))
            {
                existingData.push_back(Line);
            }
            inFile.close();
            ofstream outFile("SaveUserData/UserData.txt");

            outFile << username << " \t Won \t " << duration.count() << "\t" << timeString.substr(0,timeString.length()-2) << "\t" << name << endl;
            for (const auto &data : existingData)
            {
                outFile << data << "\n";
            }
            outFile.close();
            ifstream Data("SaveUserData/UserData.txt");
            string line;
            while (getline(Data, line))
            {
                stringstream ss(line);
                string nameofplayer, action, timeduration, day, month, date, time, year, nameofmap;
                ss >> nameofplayer >> action >> timeduration >> day >> month >> date >> time >> year >> nameofmap;
                if (nameofplayer == username)
                    TotalGames++;
                if (nameofplayer == username && action == "Won")
                    WonGames++;
                if (nameofplayer == username)
                    AllDurationSpent += stoi(timeduration);
                if (nameofplayer == username && FindLastWin && action == "Won" && LastWinDay != "null")
                {
                    LastWinDay = day;
                    LastWinMonth = month;
                    LastWinDate = date;
                    LastWinTime = time;
                    LastWinYear = year;
                    FindLastWin = false;
                }
            }
            Data.close();
            system("cls");
            cout << MAGENTA << "Congratulations " << username << ".You won!" << RESET << endl;
            cout << "You've played " << TotalGames << " Games" << endl;
            cout << "You've won " << WonGames << " Games" << endl;
            cout << "You've spent " << AllDurationSpent << " seconds" << endl;
            cout << "Your last won game was at " << LastWinYear << " / " << LastWinMonth << " / " << LastWinDay << "   " << LastWinTime << endl;
            Sleep(10000);
            system("cls");
            return;
        }
        if (lose)
        {
            string LastWinDay, LastWinMonth, LastWinDate, LastWinTime, LastWinYear;
            int TotalGames = 0, WonGames = 0, AllDurationSpent = 0;
            system("cls");
            ifstream inFile("SaveUserData/UserData.txt");
            vector<string> existingData;
            string Line;
            while (getline(inFile, Line))
            {
                existingData.push_back(Line);
            }
            inFile.close();
            ofstream outFile("SaveUserData/UserData.txt");

            outFile << username << " \t Lost \t " << duration.count() << "\tnull"
                    << "\tnull"
                    << "\tnull"
                    << "\tnull"
                    << "\tnull"
                    << "\t" << name << endl;
            for (const auto &data : existingData)
            {
                outFile << data << "\n";
            }
            outFile.close();
            ifstream Data("SaveUserData/UserData.txt");
            string line;
            while (getline(Data, line))
            {
                stringstream ss(line);
                string nameofplayer, action, timeduration, day, month, date, time, year, nameofmap;
                ss >> nameofplayer >> action >> timeduration >> day >> month >> date >> time >> year >> nameofmap;
                if (nameofplayer == username)
                    TotalGames++;
                if (nameofplayer == username && action == "Won")
                    WonGames++;
                if (nameofplayer == username)
                    AllDurationSpent += stoi(timeduration);
                if (nameofplayer == username && action == "Won" && LastWinDay == "")
                {
                    LastWinDay = day;
                    LastWinMonth = month;
                    LastWinDate = date;
                    LastWinTime = time;
                    LastWinYear = year;
                }
            }
            Data.close();
            system("cls");
            cout << MAGENTA << "Sorry dear " << username << ".You lost!" << RESET << endl;
            cout << "You've played " << TotalGames << " Games" << endl;
            cout << "You've won " << WonGames << " Games" << endl;
            cout << "You've spent " << AllDurationSpent << " seconds" << endl;
            if (LastWinTime != "")
        
                cout << "Your last won game was at " << LastWinYear << " / " << LastWinMonth << " / " << LastWinDay << "   " << LastWinTime << endl;
            else
                cout << "You haven't won any game";
            Sleep(10000);
            system("cls");
            return;
        }
        for (int i = 0; i < row; ++i)
            delete[] map[i];
        delete[] map;
        break;
    }
    case '3':
        system("cls");
        return;

    default:
        system("cls");
        cout << "Please press a valid key" << endl;
        break;
    }
}

void History()
{
}

void Leaderboard()
{
}

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

void PathMakerHard(int row, int col, int len, int min, int max, int **&map)
{
    // it works only on even_rowed maps for now
    int i_pos = 0, j_pos = 0, sum = 0, range, diff;
    range = max - min + 1;
    while (1)
    {
        if (i_pos % 2 == 0)
        {
            for (int i = 0; i < col; i++)
            {
                int rnd = rand() % range + min;
                while (rnd == 0)
                {
                    rnd = rand() % range + min;
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

void SolveMazeSection()
{
    char input = 0;
    while (input != '3')
    {
        cout << "1. Enter the name of map\n   (The file exists in Maps/ directory)\n"
             << endl;
        cout << "2. Quit" << endl;
        input = _getch();
        switch (input)
        {
        case '1':
            system("cls");
            SolveMaze();
            break;
        case '2':
            system("cls");
            return;

        default:
            system("cls");
            cout << "Please press a valid key" << endl;
            break;
        }
    }
}

void SolveMaze()
{
    cout << "Please enter the name of txt file:\n(example: test.txt)\n";
    string path = "Maps";
    for (const auto &entry : fs::directory_iterator(path))
    {
        cout << entry.path().filename() << endl;
    }
    string name;
    cin >> name;
    system("cls");
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

    int startX = 0, startY = 0;
    int endRow = row - 1, endCol = col - 1;
    int pathSum = 0;
    int shortestPath = INT_MAX;
    int **maze_keeper = PlateMaker(row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            maze_keeper[i][j] = map[i][j];
        }
    }

    if (bruteForce(map, row, col, startX, startY, endRow, endCol, pathSum, shortestPath, ans))
    {
        ShowPath(row, col, maze_keeper, ans);
    }
    else
    {
        cout << "No path found" << endl;
    }

    PlateDeleter(row, map);
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

bool bruteForce(int **maze, int rows, int cols, int startX, int startY, int endRow, int endCol, int pathSum, int &shortestPath, int **&ans)
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

    if (bruteForce(new_maze, rows, cols, startX + 1, startY, endRow, endCol, pathSum, shortestPath, ans) ||
        bruteForce(new_maze, rows, cols, startX - 1, startY, endRow, endCol, pathSum, shortestPath, ans) ||
        bruteForce(new_maze, rows, cols, startX, startY + 1, endRow, endCol, pathSum, shortestPath, ans) ||
        bruteForce(new_maze, rows, cols, startX, startY - 1, endRow, endCol, pathSum, shortestPath, ans))
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

void ColorizeAndMonitor(int row, int col, int **map, int Pos_x, int Pos_y, int pathSum, vector<int> vis_i, vector<int> vis_j)
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
            bool checkifprinted = false, checkifvisited = false;
            int lengthofnumber = to_string(map[i][j]).size();
            cout << '|';
            for (int k = 1; k <= (MaxLength - lengthofnumber) + 2; k += 2)
            {
                cout << ' ';
            }
            if (i == Pos_x && j == Pos_y)
            {
                cout << RED << map[i][j] << RESET;
                checkifprinted = true;
            }
            if (!checkifprinted)
            {
                for (int m = 0; m < vis_i.size(); m++)
                {
                    for (int n = m; n <= m; n++)
                    {
                        if (i == vis_i[m] && j == vis_j[n])
                        {
                            cout << GREEN << map[i][j] << RESET;
                            checkifvisited = true;
                        }
                    }
                }
            }
            if (!checkifprinted && !checkifvisited)
            {
                if (map[i][j] == 0)
                    cout << YELLOW << map[i][j] << RESET;
                else
                    cout << map[i][j];
            }
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
    cout << CYAN << "current pathsum is :   " << GREEN << pathSum << endl;
    cout << MAGENTA << "Press 'q' to exit from this section" << RESET;
}