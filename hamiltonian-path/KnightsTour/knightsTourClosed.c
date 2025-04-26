#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

// check if the final location is within a knights move of the starting position
bool is_closed_tour(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int new_x = x + move_x[i];
        int new_y = y + move_y[i];
        if (new_x == 0 && new_y == 0) {
            return true;
        }
    }
    return false;
}

// count the number of onward valid moves from position (x, y)
int get_degree(int x, int y, int board[N][N]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int new_x = x + move_x[i];
        int new_y = y + move_y[i];
        if (is_valid_move(new_x, new_y, board)) {
            count++;
        }
    }
    return count;
}

// struct to hold moves
typedef struct {
    int x, y, degree;
} Move;

// sort moves
int compare_moves(const void *a, const void *b) {
    return ((Move *)a)->degree - ((Move *)b)->degree;
}


bool knight_tour(int x, int y, int move_count, int board[N][N]) {
    if (move_count == N * N) {
        return is_closed_tour(x, y);
    }

    Move moves[8];
    int count = 0;

    for (int i = 0; i < 8; i++) {
        int new_x = x + move_x[i];
        int new_y = y + move_y[i];
        if (is_valid_move(new_x, new_y, board)) {
            moves[count].x = new_x;
            moves[count].y = new_y;
            moves[count].degree = get_degree(new_x, new_y, board);
            count++;
        }
    }

    // sort moves using Warnsdorff’s Rule
    qsort(moves, count, sizeof(Move), compare_moves);

    for (int i = 0; i < count; i++) {
        int nx = moves[i].x;
        int ny = moves[i].y;
        board[nx][ny] = move_count;
        if (knight_tour(nx, ny, move_count + 1, board)) {
            return true;
        }
        board[nx][ny] = -1;  // backtrack
    }

    return false;
}


bool solve_knights_tour() {
    int board[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }

    board[0][0] = 0;

    if (!knight_tour(0, 0, 1, board)) {
        printf("Closed Knight's Tour solution does not exist\n");
        return false;
    }

    print_board(board);
    printf("The tour is closed!\n");
    return true;
}

int main() {
    printf("Starting Closed Knight's Tour...\n");
    solve_knights_tour();
    return 0;
}
