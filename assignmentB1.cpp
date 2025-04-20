#include <iostream>
using namespace std;

const int MAX = 20; // max board size

int board[MAX][MAX]; // 2D board array

bool isSafe(int row, int col, int n) {
    // Check this column in previous rows
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j]) return false;

    return true;
}

bool solveNQueens(int row, int n) {
    if (row == n) return true;

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, n)) {
            board[row][col] = 1;
            if (solveNQueens(row + 1, n)) return true;
            board[row][col] = 0; // backtrack
        }
    }
    return false;
}

void printBoard(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "|";
            if (board[i][j]) cout << "X";
            else cout << " ";
        }
        cout << "|" << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    // Initialize board
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    if (solveNQueens(0, n)) {
        cout << "\nSolution:\n";
        printBoard(n);
    } else {
        cout << "No solution exists for " << n << " queens.\n";
    }

    return 0;
}
