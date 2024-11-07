#include <iostream>
#include <vector>

using namespace std;

// Function to print the n x n chessboard
void printBoard(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check the row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i] == 1) {
            return false;
        }
    }

    // Check the upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check the lower diagonal on the left side
    for (int i = row, j = col; j >= 0 && i < n; i++, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Recursive function to solve the N-Queens problem using backtracking
bool solveNQueens(vector<vector<int>>& board, int col, int n, int preRow, int preCol) {
    // If all queens are placed, return true
    if (col >= n) {
        return true;
    }

    // Skip the column where the first queen is already placed
    if (col == preCol) {
        return solveNQueens(board, col + 1, n, preRow, preCol);
    }

    // Try placing queens in all rows of this column
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            // Place the queen
            board[i][col] = 1;

            // Recursively place the rest of the queens
            if (solveNQueens(board, col + 1, n, preRow, preCol)) {
                return true;
            }

            // If placing the queen in board[i][col] doesn't lead to a solution, backtrack
            board[i][col] = 0;
        }
    }

    // If the queen cannot be placed in any row in this column, return false
    return false;
}

int main() {
    int n, row, col;

    cout << "Enter the size of the chessboard (n): ";
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));

    cout << "Enter the row and column of the first queen (0-based index): ";
    cin >> row >> col;

    // Place the first queen at the given position
    board[row][col] = 1;

    // Solve the N-Queens problem with the first queen pre-placed
    if (!solveNQueens(board, 0, n, row, col)) {
        cout << "No solution exists.\n";
    } else {
        cout << "Final N-Queen Matrix:\n";
        printBoard(board, n);
    }

    return 0;
}
