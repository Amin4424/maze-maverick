#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

void map(int, int);
int main()
{
    while (1)
    {
        cout<<"1. Create a New Map"<<endl;
        cout<<"2. Playground"<<endl;
        cout<<"3. Solve a Maze"<<endl;
        cout<<"4. History"<<endl;
        cout<<"5. Leaderboard"<<endl;
        cout<<"6. Exit"<<endl;

        char input = _getch();
        switch (input)
        {
        case '1':
        system("cls");
            break;
        
        case '2':
        system("cls");
            break;
        
        case '3':
        system("cls");    
            break;
        
        case '4':
        system("cls");    
            break;
        
        case '5':
        system("cls");    
            break;
        
        case '6':
        system("cls");    
            break;
        
        default:
        system("cls");
        cout << "Please press a valid key" << endl;
            break;
        }
    }
    
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
