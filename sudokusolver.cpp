#include <iostream>
#include <vector>

using namespace std;

#define N 9

// Function to print the Sudoku grid
void printGrid(vector<vector<int>> &grid) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a given position
bool isSafe(vector<vector<int>> &grid, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < N; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(vector<vector<int>> &grid, int row, int col) {
    // If we have reached the last cell
    if (row == N - 1 && col == N) {
        return true;
    }

    // If column value becomes 9, move to next row and column start from 0
    if (col == N) {
        row++;
        col = 0;
    }

    // If the current position is already filled, move to the next cell
    if (grid[row][col] > 0) {
        return solveSudoku(grid, row, col + 1);
    }

    // Try filling the cell with numbers 1 to 9
    for (int num = 1; num <= 9; ++num) {
        // Check if it's safe to place the number
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Check for next possibility with next column
            if (solveSudoku(grid, row, col + 1)) {
                return true;
            }
        }

        // Remove the number if it doesn't lead to a solution
        grid[row][col] = 0;
    }

    // If no number can be placed in the current cell, return false
    return false;
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid, 0, 0)) {
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}
