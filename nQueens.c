#include <stdio.h>
#define N 8  // Change N for different board sizes

void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j] ? 'Q' : '.');
        printf("\n");
    }
    printf("\n");
}

// Function to check if placing a queen at (row, col) is safe
int isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check the same column (above rows)
    for (i = 0; i < row; i++)
        if (board[i][col]) return 0;

    // Check upper-left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return 0;

    // Check upper-right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return 0;

    return 1;  // If no conflicts, placement is safe
}

// Recursive function to place queens row by row
int solveNQueens(int board[N][N], int row) {
    if (row >= N) {
        printSolution(board);  // Print solution when all queens are placed
        return 1;
    }

    int success = 0;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  // Place queen
            success = solveNQueens(board, row + 1) || success;
            board[row][col] = 0;  // Backtrack if needed
        }
    }
    return success;
}

int main() {
    int board[N][N] = {0};  // Initialize board with all 0s
    if (!solveNQueens(board, 0))
        printf("No solution found\n");
    return 0;
}
