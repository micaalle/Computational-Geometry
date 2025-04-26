#include <stdio.h>
#include <stdbool.h>

#define N 8  

int move_x[] = {2, 1, -1, -2, -2, -1, 1, 2};
int move_y[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool is_valid_move(int x, int y, int board[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}


void print_board(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

bool knight_tour(int x, int y, int move_count, int board[N][N]) {
    if(move_count == N * N) return true;

    for (int i = 0; i < 8; i++) {
        int new_x = x + move_x[i];
        int new_y = y + move_y[i];
        if (is_valid_move(new_x, new_y, board)) {
            board[new_x][new_y] = move_count;
            if (knight_tour(new_x, new_y, move_count + 1, board)) {
                return true;
            }
            board[new_x][new_y] = -1;
        }
    }
    return false;
}


bool solve_knights_tour() {
    int board[N][N];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = -1;
        }
    }

    board[0][0] = 0;

    if (!knight_tour(0, 0, 1, board)) {
        printf("does not exist\n");
        return false;
    }

    print_board(board);
    return true;
}

int main() {
    solve_knights_tour();
    return 0;
}
