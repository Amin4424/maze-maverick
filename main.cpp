#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int **PlateMaker(int row, int col);
int **PathMaker(int row, int col, int **plate);

int main()
{
    int **plate;
    int row, col;
    cin >> row >> col;
    plate = PlateMaker(row, col);

    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < col; j++)
    //         cout << *(*(plate + i) + j) << ' ';

    //     cout << endl;
    // }

    return 0;
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

// int **PathMaker(int row, int col, int **plate)
// {
//     int x_pos = row, y_pos = 0, sum = 0;
//     while (x_pos != 0 || y_pos != col)
//     {
//         if (x_pos != 0)
//             for (int i = 0; i <= rand() % x_pos; i++)
//             {
//                 while (*(*(plate+x_pos)+y_pos) == 0)
//                     *(*(plate+x_pos)+y_pos) = rand() % 21 - 10;

//                 sum += *(*(plate+x_pos)+y_pos);
//                 x_pos--;
//             }

//         if (col - y_pos != 0)
//             for (int i = 0; i <= rand() % (col - y_pos); i++)
//             {
//                 while (*(*(plate+x_pos)+y_pos) == 0)
//                     *(*(plate+x_pos)+y_pos) = rand() % 21 - 10;

//                 sum += *(*(plate+x_pos)+y_pos);
//                 y_pos++;
//             }
//     }

//     return plate;
// }