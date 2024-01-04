#include <iostream>
#include <climits>
using namespace std;
//recursives
bool solveMaze(int **maze, int rows, int cols, int startX, int startY, int endRow, int endCol, int pathSum, int &shortestPath) {
    if (startX < 0 || startX >= rows || startY < 0 || startY >= cols || maze[startX][startY] == 0) {
        return false;
    }

    if (startX == endRow && startY == endCol) {
        if (pathSum == maze[endRow][endCol]) {
            if (pathSum < shortestPath) {
                shortestPath = pathSum;
            }
            return true;
        } else {
            return false;
        }
    }

    pathSum += maze[startX][startY];
    maze[startX][startY] = 0;

    if (solveMaze(maze, rows, cols, startX + 1, startY, endRow, endCol, pathSum, shortestPath) ||
        solveMaze(maze, rows, cols, startX - 1, startY, endRow, endCol, pathSum, shortestPath) ||
        solveMaze(maze, rows, cols, startX, startY + 1, endRow, endCol, pathSum, shortestPath) ||
        solveMaze(maze, rows, cols, startX, startY - 1, endRow, endCol, pathSum, shortestPath)) {
        return true;
    }

    return false;
}

int main() {
    int rows, cols;
    cin >> rows >> cols;

    int **maze = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        maze[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> maze[i][j];
        }
    }

    int startX = 0, startY = 0;
    int endRow = rows - 1, endCol = cols - 1;
    int pathSum = 0;
    int shortestPath = INT_MAX;

    if (solveMaze(maze, rows, cols, startX, startY, endRow, endCol, pathSum, shortestPath)) {
        cout << "Shortest path length: " << shortestPath << endl;
    } else {
        cout << "No path found";
    }

    for (int i = 0; i < rows; ++i) {
        delete[] maze[i];
    }
    delete[] maze;

    return 0;
}
