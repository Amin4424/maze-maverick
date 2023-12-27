#include <iostream>
#include <time.h>

using namespace std;


int **PlateMaker(int row, int col);
void **PathMaker(int row, int col, int **&plate);

int main()
{
    int **plate;
    int row, col;
    cin >> row >> col;
    plate = PlateMaker(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            plate[i][j] = 0;
    }

    PathMaker(row, col, plate);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cout << *(*(plate + i) + j) << ' ';

        cout << endl;
    }

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

void **PathMaker(int row, int col, int **&plate)
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