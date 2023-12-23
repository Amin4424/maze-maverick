#include <iostream>
using namespace std;

void map(int, int);
int main()
{

    int row, col;
    cin >> row >> col;
    map(row, col);
    return 0;
}
//Map section
void map(int row, int col)
{

    for (int k = 1; k <= row; k++)
    {
        for (int i = 1; i <= col; i++)
        {
            cout << "+----";
        }
        cout << "+" << endl;
        for (int j = 1; j <= col; j++)
        {
            cout << "| 01 ";
        }
        cout << "|" << endl;
    }
    for (int i = 1; i <= col; i++)
    {
        cout << "+----";
    }
    cout << "+" << endl;
}
