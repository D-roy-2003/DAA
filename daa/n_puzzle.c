//n puzzle
#include <stdio.h>
#include <stdlib.h>

#define N 3

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int isSolvable(int puzzle[N * N]) {
    int inv_count = 0;
    for (int i = 0; i < N * N - 1; i++) {
        for (int j = i + 1; j < N * N; j++) {
            if (puzzle[j] && puzzle[i] && puzzle[i] > puzzle[j])
                inv_count++;
        }
    }
    return (inv_count % 2 == 0);
}

int main() {
    int puzzle[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    int flat_puzzle[N * N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            flat_puzzle[i * N + j] = puzzle[i][j];
        }
    }

    if (isSolvable(flat_puzzle))
        printf("Puzzle is solvable\n");
    else
        printf("Puzzle is not solvable\n");

    return 0;
}
