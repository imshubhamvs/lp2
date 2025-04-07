#include <bits/stdc++.h>
using namespace std;

class Queens {
private:
    int size;
    int **board;

public:
    Queens(int n) {
        size = n;
        board = new int *[n];
        for (int i = 0; i < n; i++) {
            board[i] = new int[n];
            fill(board[i], board[i] + n, 0);
        }
    }

    ~Queens() {
        for (int i = 0; i < size; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    void do_visit(int row, int column) {
        for (int i = 0; i < size; i++) {
            board[row][i]++;
            board[i][column]++;
        }

        // diagonals
        for (int i = row, j = column; i < size && j < size; i++, j++)
            board[i][j]++;
        for (int i = row, j = column; i >= 0 && j >= 0; i--, j--)
            board[i][j]++;
        for (int i = row, j = column; i < size && j >= 0; i++, j--)
            board[i][j]++;
        for (int i = row, j = column; i >= 0 && j < size; i--, j++)
            board[i][j]++;

        // Correct for overcounting the (row, column) cell
        board[row][column] -= 5;
    }

    void undo_visit(int row, int column) {
        for (int i = 0; i < size; i++) {
            board[row][i]--;
            board[i][column]--;
        }

        // diagonals
        for (int i = row, j = column; i < size && j < size; i++, j++)
            board[i][j]--;
        for (int i = row, j = column; i >= 0 && j >= 0; i--, j--)
            board[i][j]--;
        for (int i = row, j = column; i < size && j >= 0; i++, j--)
            board[i][j]--;
        for (int i = row, j = column; i >= 0 && j < size; i--, j++)
            board[i][j]--;

        // Correct for over-removing the (row, column) cell
        board[row][column] += 5;
    }

    bool Nqueens(int curr_row) {
        if (curr_row == size)
            return true;

        for (int i = 0; i < size; i++) {
            if (board[curr_row][i] == 0) {
                do_visit(curr_row, i);
                board[curr_row][i] = -1;  // Place queen
                if (Nqueens(curr_row + 1))
                    return true;
                board[curr_row][i] = 0;   // Remove queen
                undo_visit(curr_row, i);
            }
        }
        return false;
    }

    void solve() {
        if (Nqueens(0)) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board[i][j] == -1) {
                        cout << "(" << i << "," << j << "), ";
                    }
                }
            }
            cout << endl;
        } else {
            cout << "No solution exists.\n";
        }
    }
};

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;
    Queens q(n);
    q.solve();
    return 0;
}
