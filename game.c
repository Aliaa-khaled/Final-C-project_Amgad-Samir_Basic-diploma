#include <stdio.h>
#include "game.h"

Move* moveHistory = NULL;

void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

enum MoveStatus isMoveValid(char board[3][3], int move) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (move < 1 || move > 9) {
        return MOVE_OUT_OF_RANGE;
    }
    if (board[row][col] != ' ') {
        return MOVE_SPOT_TAKEN;
    }
    return MOVE_VALID;
}

// دالة للتحقق من امتلاء اللوحة
enum BoardStatus isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return BOARD_HAS_EMPTY_SPOTS;
            }
        }
    }
    return BOARD_FULL;
}

enum WinStatus checkWin(char board[3][3], char symbol) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return WIN_ROW;
        }
    }

    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
            return WIN_COLUMN;
        }
    }

    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
        return WIN_DIAGONAL;
    }

    return WIN_NONE;
}

void addMove(int player, int move) {
    Move* newMove = (Move*) malloc(sizeof(Move));
    newMove->player = player;
    newMove->move = move;
    newMove->next = moveHistory;
    moveHistory = newMove;
}

void undoLastMove(char board[3][3]) {
    if (moveHistory != NULL) {
        int lastMove = moveHistory->move;
        int row = (lastMove - 1) / 3;
        int col = (lastMove - 1) % 3;
        board[row][col] = ' ';
        Move* temp = moveHistory;
        moveHistory = moveHistory->next;
        free(temp);
    }
}
