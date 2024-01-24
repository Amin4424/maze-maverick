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
#include <set>
#include <unordered_set>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define BLACK "\033[30m"
#define WHITE "\033[37m"
#define BackgroundBLACK "\033[40m"
#define BackgroundRED "\033[41m"
#define BackgroundGREEN "\033[42m"
#define BackgroundYELLOW "\033[43m"
#define BackgroundBLUE "\033[44m"
#define BackgroundMAGENTA "\033[45m"
#define BackgroundCYAN "\033[46m"
#define BackgroundWHITE "\033[47m"
using namespace std;
namespace fs = filesystem;

struct GameData
{
    string username;
    string action;
    int timeduration;
    string day;
    string month;
    string date;
    string time;
    string year;
    string nameofmap;
    int wingames;
};

struct GameDataForUniqueFile
{
    string username;
    int timeduration;
    int wingames;
};

void StartProgram();
void CreateMapSection();
void CreateMapEasy();
void CreateMapHard();
int **PlateMaker(int row, int col);
void PathMaker(int row, int col, int sum, int min, int max, int **&plate);
void PathMakerHard(int row, int col, int len, int min, int max, int **&plate);
void Blocker(int Bmin, int Bmax, int row, int col, int **&maze);
void ShowPath(int row, int col, int **&map, int **&maze);
void PlaygroundSection();
void Playground(string mapname);
void ColorizeAndMonitor(int row, int col, int **map, int Pos_x, int Pos_y, int pathSum, vector<int> vis_i, vector<int> vis_j);
void SolveMazeSection();
void SolveMaze(string address);
bool bruteForce(int **maze, int rows, int cols, int startX, int startY, int endRow, int endCol, int pathSum, int pathlenght, int lenghtOfPath, int &shortestPath, int **&ans);
void monitor(int row, int col, int **path, int **map);
void History();
void UserInfo();
void LeaderBoard();
void PlateDeleter(int row, int **&plate);

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
        cout << CYAN << "5. User Info" << endl;
        cout << BackgroundBLACK << WHITE << "6. LeaderBoard" << endl;
        cout << MAGENTA << "7. Exit" << endl;
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
            History();
            break;
        case '5':
            system("cls");
            UserInfo();
            break;
        case '6':
            system("cls");
            LeaderBoard();
            break;

        case '7':
            system("cls");
            cout << "Exiting the program...";
            exit(0);
            break;

        default:
            system("cls");
            cout << MAGENTA << "Please press a valid key" << RESET << endl;
            Sleep(1500);
            system("cls");
            break;
        }
    }
}

void CreateMapSection()
{
    char input = 0;
    while (input != '3')
    {
        cout << RED << "1. Easy" << endl;
        cout << CYAN << "2. Hard" << endl;
        cout << GREEN << "3. Quit" << endl;
        cout << WHITE;
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
            cout << MAGENTA << "Please press a valid key" << RESET << endl;
            Sleep(1500);
            system("cls");
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
        while (!(cin >> row))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (row <= 0);

    do
    {
        cout << "Enter the number of columns:\n";
        while (!(cin >> col))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (col <= 0);

    string mapname;
    cout << "Enter your map name:\n";
    cin >> mapname;

    int **map = PlateMaker(row, col);

    PathMaker(row, col, 0, -3, 3, map);

    int **path = PlateMaker(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            path[i][j] = map[i][j];
        }
    }

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

    system("cls");
    monitor(row, col, path, map);
    PlateDeleter(row, map);
    PlateDeleter(row, path);
}

void CreateMapHard()
{
    int row, col, len, min, max, minB, maxB;
    do
    {
        cout << "Enter the number of rows:\n";
        while (!(cin >> row))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (row <= 0);

    do
    {
        cout << "Enter the number of columns:\n";
        while (!(cin >> col))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (col <= 0);

    do
    {
        cout << "Enter the lenght of path:\n";
        while (!(cin >> len))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        if ((len < (row + col - 2)) || (len >= (row * col)) || ((len - (row + col - 2)) % 2 != 0) || ((row % 2 == 0) && (col % 2 == 0) && (len == row * col - 1)))
        {
            cout << "Invalid path!\n";
        }

    } while ((len < (row + col - 2)) || (len >= (row * col)) || ((len - (row + col - 2)) % 2 != 0) || ((row % 2 == 0) && (col % 2 == 0) && (len == row * col - 1)));

    cout << "Enter the minimum amount of each block:\n";
    while (!(cin >> min))
    {
        cout << "Integer wanted" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    do
    {
        cout << "Enter the maximum amount of each block:\n";
        while (!(cin >> max))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (max < min);

    do
    {
        cout << "Enter the minimum number of blocked blocks:\n";
        while (!(cin >> minB))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (minB > (row * col - len - 1));

    do
    {
        cout << "Enter the maximum number of blocked blocks:\n";
        while (!(cin >> maxB))
        {
            cout << "Integer wanted" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while ((maxB > (row * col - len - 1)) || maxB < minB);

    string mapname;
    cout << "Enter your map name:\n";
    cin >> mapname;

    int **map = PlateMaker(row, col);
    PathMakerHard(row, col, len, min, max, map);

    int **ans = PlateMaker(row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            ans[i][j] = map[i][j];
        }
    }

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

    system("cls");
    monitor(row, col, map, ans);

    PlateDeleter(row, map);
    PlateDeleter(row, ans);
}

void PlaygroundSection()
{
    while (1)
    {
        cout << MAGENTA << "Choose your option: \n";
        cout << CYAN << "1. Choosing a map from pre-made maps \n";
        cout << GREEN << "2. Reading a map\n";
        cout << RED << "3. Quit\n"
             << RESET;
        char option;
        string address;
        string nameofmap;
        option = _getch();

        switch (option)
        {
        case '1':
        {
            fs::path folderPath = "Maps";
            if (fs::is_directory(folderPath))
            {
                system("cls");
                string path = "Maps";
                cout << MAGENTA << "Choose the map:" << endl
                     << RESET;
                cout << "-----------\n";
                for (const auto &entry : fs::directory_iterator(path))
                {
                    cout << YELLOW << entry.path().filename() << RESET << endl
                         << RESET;
                }
                cout << "-----------\n";
                string locatedmaps = "Maps/";

                cin >> nameofmap;
                locatedmaps += nameofmap;
                Playground(locatedmaps);
            }
            else
            {
                system("cls");
                cerr << MAGENTA << "Unable to find the file" << RESET << endl;
                Sleep(1000);
                system("cls");
                return;
            }
            break;
        }
        case '2':
            system("cls");
            cout << "Please type a valid address to open the file : \n";
            getline(cin, address);
            Playground(address);
            break;
        case '3':

            system("cls");
            return;

        default:
            system("cls");
            cout << MAGENTA << "Please press a valid key" << RESET << endl;
            Sleep(1500);
            system("cls");
            break;
        }
    }
}

void History()
{
    ifstream file("SaveUserData/UserData.txt");
    system("cls");
    if (file.is_open())
    {
        cout << YELLOW << "Playername\t"
             << "  Game status\t"
             << "    spend time\t"
             << "                 Date\t"
             << "\t          Name of the map\n"
             << RESET;
        cout << "--------------------------------------------------------------------------------------------------------\n"
             << BLUE;
        int linesToRead = 10;
        string line;

        while (linesToRead > 0 && getline(file, line))
        {
            cout << line << endl;
            linesToRead--;
        }

        file.close();
    }
    else
    {
        system("cls");
        cerr << MAGENTA << "Unable to open file" << RESET;
        Sleep(1000);
        system("cls");
        return;
    }
    cout << RESET << "--------------------------------------------------------------------------------------------------------\n";
    cout << MAGENTA << "Press any key to go back to menu" << RESET;
    _getch();
    system("cls");
    return;
}

void UserInfo()
{
    ifstream file("SaveUserData/UserData.txt");
    vector<string> users;
    int CounterForUsers = 0, CounterForChecking = 0;
    if (file.is_open())
    {
        cout << MAGENTA << "Type a username to get the info\n"
             << RESET;
        cout << "------------" << endl;
        string line;
        unordered_set<string> uniqueNames;
        while (getline(file, line))
        {
            string playerName = line.substr(0, line.find_first_of(" \t"));
            uniqueNames.insert(playerName);
            users.push_back(playerName);
            CounterForUsers++;
        }

        file.close();
        for (const auto &name : uniqueNames)
        {
            cout << YELLOW << name << RESET << endl;
        }
        cout << "------------" << endl;
    }
    else
    {
        cerr << MAGENTA << "Unable to open file" << RESET << endl;
        Sleep(1000);
        system("cls");
        return;
    }
    string username;
    cin >> username;
    for (int i = 0; i < CounterForUsers; i++)
    {
        if (username != users[i])
        {
            CounterForChecking++;
        }
    }
    if (CounterForChecking == CounterForUsers)
    {
        system("cls");
        cout << MAGENTA << "Invalid username ." << RESET;
        Sleep(3000);
        system("cls");
        return;
    }
    ifstream data("SaveUserData/UserData.txt");
    if (!data.is_open())
    {
        cout << MAGENTA << "Failed to open file" << RESET << endl;
        return;
    }

    set<string> uniqueNames;
    vector<GameData> userGames;

    string line;
    while (getline(data, line))
    {
        stringstream ss(line);
        GameData game;
        ss >> game.username >> game.action >> game.timeduration >> game.day >> game.month >> game.date >> game.time >> game.year >> game.nameofmap;
        uniqueNames.insert(game.username);
        if (game.username == username)
        {
            userGames.push_back(game);
        }
    }
    data.close();

    int TotalGames = 0, WonGames = 0, AllDurationSpent = 0;
    string LastWinDate, LastWinDay, LastWinMonth, LastWinTime, LastWinYear;

    for (const auto &game : userGames)
    {
        TotalGames++;
        if (game.action == "Won")
        {
            WonGames++;
            if (LastWinYear.empty())
            {
                LastWinDay = game.day;
                LastWinMonth = game.month;
                LastWinDate = game.date;
                LastWinTime = game.time;
                LastWinYear = game.year;
            }
        }
        AllDurationSpent += game.timeduration;
    }
    system("cls");
    cout << GREEN << "Total games of player " << YELLOW << username << GREEN << " is " << CYAN << TotalGames << endl;
    cout << GREEN << "Total win games of player " << YELLOW << username << GREEN << " is " << CYAN << WonGames << endl;

    if (LastWinTime != "")
        cout << YELLOW << username << GREEN << " last won game was at " << CYAN << LastWinYear << RESET << " / " << CYAN << LastWinMonth << RESET << " / " << CYAN << LastWinDate << RESET << "   " << CYAN << LastWinTime << endl;

    else
        cout << YELLOW << username << GREEN << " haven't won any game\n";

    cout << GREEN << "Total spend time on game is " << CYAN << AllDurationSpent << GREEN << " seconds" << endl
         << RESET;
    Sleep(15000);
    system("cls");
    return;
}

void LeaderBoard()
{
    system("cls");
    ifstream file("SaveUserData/UniqueUsersData.txt");
    vector<GameDataForUniqueFile *> myvec;
    int counter = 0;
    if (file.is_open())
    {
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            GameDataForUniqueFile *gameptr = new GameDataForUniqueFile[1];
            ss >> gameptr->username >> gameptr->timeduration >> gameptr->wingames;
            myvec.push_back(gameptr);
            counter++;
        }
        for (int i = 0; i < counter; i++)
        {
            for (int j = i + 1; j < counter; j++)
            {
                if (myvec[j]->wingames > myvec[i]->wingames)
                {
                    GameDataForUniqueFile *temp = myvec[i];
                    myvec[i] = myvec[j];
                    myvec[j] = temp;
                }
                else if (myvec[j]->wingames == myvec[i]->wingames)
                {
                    if (myvec[j]->timeduration < myvec[i]->timeduration)
                    {
                        GameDataForUniqueFile *temp = myvec[i];
                        myvec[i] = myvec[j];
                        myvec[j] = temp;
                    }
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            cout << BackgroundRED <<BLUE<< i+1 << " . " << myvec[i]->username << RESET << endl;
        }
        Sleep(3000);
        system("cls");
        return;
    }

    else
    {
        cerr << MAGENTA << "Unable to open file" << RESET << endl;
    }
    file.close();
}

void monitor(int row, int col, int **path, int **map)
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
            if ((map[i][j] == path[i][j]) && (map[i][j] != 0))
            {
                cout << GREEN;
            }
            cout << map[i][j] << WHITE;
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
    int i_pos = 0, j_pos = 0, sum = 0, range;
    range = max - min + 1;
    // odd-rowed maps
    if (row % 2 == 1)
    {
        while (1)
        {
            // Going to last index of row on even rows
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
                    // Ceck if we have reached the final block
                    if ((j_pos == col - 1) && (i_pos == row - 1))
                    {
                        map[i_pos][j_pos] = sum;
                        return;
                    }
                }
                j_pos--;
                i_pos++;
            }

            // Going backward on odd rows until : (remaining len == len of the easy path of the remaining map)
            if (i_pos % 2 == 1)
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
                    j_pos--;
                    len--;
                    // Check if the mentioned codition has become true
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
                        PlateDeleter(row, tempmap);
                        return;
                    }
                }
                j_pos++;
                i_pos++;
            }
        }
    }
    // Odd-columned maps
    else if (col % 2 == 1)
    {
        while (1)
        {
            if (j_pos % 2 == 0)
            {
                for (int i = 0; i < row; i++)
                {
                    int rnd = rand() % range + min;
                    while (rnd == 0)
                    {
                        rnd = rand() % range + min;
                    }
                    map[i_pos][j_pos] = rnd;
                    sum += rnd;
                    i_pos++;
                    len--;
                    if ((i_pos == row - 1) && (j_pos == col - 1))
                    {
                        map[i_pos][j_pos] = sum;
                        return;
                    }
                }
                i_pos--;
                j_pos++;
            }

            if (j_pos % 2 == 1)
            {
                for (int i = 0; i < row; i++)
                {
                    int rnd = rand() % range + min;
                    while (rnd == 0)
                    {
                        rnd = rand() % range + min;
                    }
                    map[i_pos][j_pos] = rnd;
                    sum += rnd;
                    i_pos--;
                    len--;
                    if (((col - j_pos - 1) + (row - i_pos - 1) - 2) == len)
                    {
                        i_pos++;
                        j_pos++;
                        int tempcol = col - j_pos;
                        int temprow = row - i_pos;
                        int **tempmap = PlateMaker(temprow, tempcol);
                        PathMaker(temprow, tempcol, sum, min, max, tempmap);
                        for (int x = 0; x < temprow; x++)
                        {
                            for (int y = 0; y < tempcol; y++)
                            {
                                map[x + i_pos][y + j_pos] = tempmap[x][y];
                            }
                        }
                        PlateDeleter(row, tempmap);
                        return;
                    }
                }
                i_pos++;
                j_pos++;
            }
        }
    }
    // Check if the counts of rows and cols both are even
    else if ((row % 2 == 0) && (col % 2 == 0))
    {
        // Going on algorithem until : (remaining len == len of the easy path of the remaining map)
        while ((row - i_pos - 1) + (col - j_pos - 1) < len)
        {
            // Going to the last index of row in even rows (exepted from 2 last)
            if ((i_pos % 2 == 0) && (i_pos != row - 2))
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
                }
                j_pos--;
                i_pos++;
            }
            // The row befor last one
            else if (i_pos == row - 2)
            {
                while ((row - i_pos - 1) + (col - j_pos - 1) < len)
                {
                    // one block down
                    int rnd = rand() % range + min;
                    while (rnd == 0)
                    {
                        rnd = rand() % range + min;
                    }
                    map[i_pos][j_pos] = rnd;
                    sum += rnd;
                    i_pos++;
                    len--;

                    // one block right
                    rnd = rand() % range + min;
                    while (rnd == 0)
                    {
                        rnd = rand() % range + min;
                    }
                    map[i_pos][j_pos] = rnd;
                    sum += rnd;
                    j_pos++;
                    len--;
                    // check if we have reached to the final block
                    if (len == 0)
                    {
                        map[i_pos][j_pos] = sum;
                        return;
                    }

                    // one block up
                    rnd = rand() % range + min;
                    while (rnd == 0)
                    {
                        rnd = rand() % range + min;
                    }
                    map[i_pos][j_pos] = rnd;
                    sum += rnd;
                    i_pos--;
                    len--;

                    // one block right
                    rnd = rand() % range + min;
                    while (rnd == 0)
                    {
                        rnd = rand() % range + min;
                    }
                    map[i_pos][j_pos] = rnd;
                    sum += rnd;
                    j_pos++;
                    len--;
                }
                // The mentioned condotion has become True, so we use PathMakerEasy for remaining part
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
                PlateDeleter(row, tempmap);
                return;
            }
            // Going backward on odd rows
            else if (i_pos % 2 == 1)
            {
                if (i_pos != row - 2)
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
                        j_pos--;
                        len--;
                        // Check if the mentioned condition has become true
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

void SolveMazeSection()
{
    char input = 0;

    while (input != '3')
    {
        cout << "1. Enter the name of map   (The file exists in Maps/ directory)\n";
        cout << "2. Give an address to solve the maze\n";
        cout << "3. Quit" << endl;
        string FileAddress;
        string name;
        string path = "Maps";
        fs::path folderPath = "Maps";
        input = _getch();
        switch (input)
        {
        case '1':

            if (fs::is_directory(folderPath))
            {
                system("cls");
                cout << "Choose the map:\n";
                for (const auto &entry : fs::directory_iterator(path))
                {
                    cout << YELLOW << entry.path().filename() << RESET << endl;
                }
                FileAddress = "Maps/";
                cin >> name;
                FileAddress += name;
                SolveMaze(FileAddress);
            }
            else
            {
                system("cls");
                cerr << MAGENTA << "Unable to find the file" << RESET << endl;
                Sleep(1000);
                system("cls");
                return;
            }

            break;
        case '2':
            system("cls");
            cout << "Please Give a valid address.\n";
            getline(cin, FileAddress);
            SolveMaze(FileAddress);
            break;
        case '3':
            system("cls");
            return;

        default:
            system("cls");
            cout << "Please press a valid key\n"
                 << endl;
            break;
        }
    }
}

void SolveMaze(string address)
{
    system("cls");
    ifstream file(address);
    while (!file)
    {
        system("cls");
        cout << MAGENTA << "Something went wrong!\nPlease try again:\n"
             << RESET;
        Sleep(1000);
        system("cls");
        return;
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
    int pathSum = 0, pathlenght = 0;
    int shortestPath = INT_MAX;
    int **maze_keeper = PlateMaker(row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            maze_keeper[i][j] = map[i][j];
        }
    }

    if (bruteForce(map, row, col, startX, startY, endRow, endCol, pathSum, pathlenght, 0, shortestPath, ans))
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

bool bruteForce(int **maze, int rows, int cols, int startX, int startY, int endRow, int endCol, int pathSum, int pathlenght, int lenghtOfPath, int &shortestPath, int **&ans)
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
            if (lenghtOfPath == 0)
            {
                if (pathlenght < shortestPath)
                {
                    shortestPath = pathlenght;
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
            else if (pathlenght == lenghtOfPath)
            {
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        ans[i][j] = maze[i][j];
                    }
                }
                return true;
            }
        }
        else
        {

            PlateDeleter(rows, new_maze);

            return false;
        }
    }

    pathlenght++;
    pathSum += maze[startX][startY];
    new_maze[startX][startY] = 0;

    if (bruteForce(new_maze, rows, cols, startX + 1, startY, endRow, endCol, pathSum, pathlenght, lenghtOfPath, shortestPath, ans) ||
        bruteForce(new_maze, rows, cols, startX - 1, startY, endRow, endCol, pathSum, pathlenght, lenghtOfPath, shortestPath, ans) ||
        bruteForce(new_maze, rows, cols, startX, startY + 1, endRow, endCol, pathSum, pathlenght, lenghtOfPath, shortestPath, ans) ||
        bruteForce(new_maze, rows, cols, startX, startY - 1, endRow, endCol, pathSum, pathlenght, lenghtOfPath, shortestPath, ans))
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

void Playground(string address)
{
    // it receives an address it should like Maps/... or Drive/Folder/...
    ifstream file(address);
    if (!file.is_open())
    {
        system("cls");
        cout << MAGENTA << "Error: Unable to Find file" << RESET << endl;
        Sleep(2000);
        system("cls");
        return;
    }
    //Find last Slash and t to find map name for example Maps/ali.txt  name of the map is ali.txt
    int BackSlashCounter = 0;
    int TCounter = 0;
    int Temp1, Temp2;
    for (int i = 0; i < address.size(); i++)
    {
        if (address[i] == '/')
            BackSlashCounter++;
        if (address[i] == 't')
            TCounter++;
    }
    for (int i = 0; i < address.size(); i++)
    {
        if (address[i] == '/')
        {
            BackSlashCounter--;
            if (BackSlashCounter == 0)
            {
                Temp1 = i;
            }
        }
        if (address[i] == 't')
        {
            TCounter--;
            if (TCounter == 0)
            {
                Temp2 = i;
            }
        }
    }
    string nameofmap;
    for (int i = Temp1 + 1; i <= Temp2; i++)
    {
        nameofmap += address[i];
    }
    // Reading map from the file
    Sleep(5000);
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
    //Getting a username
    system("cls");
    string username;
    cout << MAGENTA << "Enter a username please:" << endl
         << RESET;
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
    //Here we make a copy of the map and we place 0 on this map
    int **CheckIfVisited = new int *[row];
    for (int i = 0; i < row; i++)
    {
        CheckIfVisited[i] = new int[col];
    }

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
    auto start = high_resolution_clock::now(); //Start counting time from here
    ColorizeAndMonitor(row, col, map, I, J, Sum, vis_i, vis_j);
    while (1)
    {

        if (Sum == map[row - 1][col - 1] && I == row - 1 && J == col - 1)
        {
            win = true;
            break;
        }
        if (I == row - 1 && J == col - 1 && Sum != map[row - 1][col - 1] || (validmove1 && validmove2 && validmove3 & validmove4) || (CheckIfVisited[row - 2][col - 1] == 0 && CheckIfVisited[row - 1][col - 2] == 0 && (I + 1 != row - 1 && J + 1 != col - 1 && I - 1 != row - 1 && J - 1 != col - 1)))
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
                if (I != row - 1 || J != col - 1)
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
                if (I != row - 1 || J != col - 1)
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
                if (I != row - 1 || J != col - 1)
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
                if (I != row - 1 || J != col - 1)
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

        outFile << username << " \t\t    Won       \t \t" << duration.count() << "\t\t" << timeString.substr(0, timeString.length() - 1) << "\t    " << nameofmap << endl;
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
            GameData game;
            ss >> game.username >> game.action >> game.timeduration >> game.day >> game.month >> game.date >> game.time >> game.year >> game.nameofmap;
            if (username == game.username)
                TotalGames++;
            if (username == game.username && game.action == "Won")
                WonGames++;
            if (username == game.username)
                AllDurationSpent += (game.timeduration);
            if (username == game.username && game.action == "Won" && LastWinDay != "null")
            {
                LastWinDay = game.day;
                LastWinMonth = game.month;
                LastWinDate = game.date;
                LastWinTime = game.time;
                LastWinYear = game.year;
            }
        }
        vector<GameDataForUniqueFile> userGameDataForUniqueFile;

        // Read file
        ifstream input_file("SaveUserData/UniqueUsersData.txt");
        if (input_file.is_open())
        {
            string line;
            while (getline(input_file, line))
            {
                stringstream ss(line);
                GameDataForUniqueFile game;
                ss >> game.username >> game.timeduration >> game.wingames;
                userGameDataForUniqueFile.push_back(game);
            }
            input_file.close();

            // Update data for the given username
            bool foundUser = false;
            for (auto &game : userGameDataForUniqueFile)
            {
                if (game.username == username)
                {
                    foundUser = true;
                    game.timeduration = AllDurationSpent;
                    game.wingames++;
                }
            }

            // If user not found, add a new entry
            if (!foundUser)
            {
                userGameDataForUniqueFile.push_back({username, AllDurationSpent, 1});
            }

            // Write back to file
            ofstream output_file("SaveUserData/UniqueUsersData.txt");
            if (output_file.is_open())
            {
                for (const auto &game : userGameDataForUniqueFile)
                {
                    output_file << game.username << " " << game.timeduration << " " << game.wingames << endl;
                }
                output_file.close();
            }
        }
        Data.close();
        cout << MAGENTA << "\nCongratulations " << username << " . You won!" << endl;
        Sleep(3000);
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

        outFile << username << " \t\t    Lost       \t \t" << duration.count() << "\t\tnull"
                << " null"
                << " null"
                << " null"
                << " null"
                << "\t    " << nameofmap << endl;
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
            GameData game;
            ss >> game.username >> game.action >> game.timeduration >> game.day >> game.month >> game.date >> game.time >> game.year >> game.nameofmap;
            if (username == game.username)
                TotalGames++;
            if (username == game.username && game.action == "Won")
                WonGames++;
            if (username == game.username)
                AllDurationSpent += game.timeduration;
            if (username == game.username && game.action == "Won" && LastWinDay == "")
            {
                LastWinDay = game.day;
                LastWinMonth = game.month;
                LastWinDate = game.date;
                LastWinTime = game.time;
                LastWinYear = "2024";
            }
        }
        vector<GameDataForUniqueFile> userGameDataForUniqueFile;

        // Read file
        ifstream input_file("SaveUserData/UniqueUsersData.txt");
        if (input_file.is_open())
        {
            string line;
            while (getline(input_file, line))
            {
                stringstream ss(line);
                GameDataForUniqueFile game;
                ss >> game.username >> game.timeduration >> game.wingames;
                userGameDataForUniqueFile.push_back(game);
            }
            input_file.close();

            // Update data for the given username
            bool foundUser = false;
            for (auto &game : userGameDataForUniqueFile)
            {
                if (game.username == username)
                {
                    foundUser = true;
                    game.timeduration = AllDurationSpent;
                    game.wingames;
                }
            }

            // If user not found, add a new entry
            if (!foundUser)
            {
                userGameDataForUniqueFile.push_back({username, AllDurationSpent, 0});
            }

            // Write back to file
            ofstream output_file("SaveUserData/UniqueUsersData.txt");
            if (output_file.is_open())
            {
                for (const auto &game : userGameDataForUniqueFile)
                {
                    output_file << game.username << " " << game.timeduration << " " << game.wingames << endl;
                }
                output_file.close();
            }
        }
        Data.close();
        cout << MAGENTA << "\nSorry dear " << username << ".You lost!" << RESET << endl;
        Sleep(3000);
        system("cls");
        return;
    }
    for (int i = 0; i < row; ++i)
        delete[] map[i];
    delete[] map;
    return;
}