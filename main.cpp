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
//Map Section
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
    cout << "|"<<endl;
  }
  for (int j = 0; j < col; j++)
  {
    cout << "+----";
  }
  cout << "+" << endl;
}
