#include <iostream>
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