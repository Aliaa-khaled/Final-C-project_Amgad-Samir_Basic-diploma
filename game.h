#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdlib.h>

enum MoveStatus {
    MOVE_VALID,
    MOVE_OUT_OF_RANGE,
    MOVE_SPOT_TAKEN
};

enum BoardStatus {
    BOARD_FULL,
    BOARD_HAS_EMPTY_SPOTS
};

enum WinStatus {
    WIN_NONE,
    WIN_ROW,
    WIN_COLUMN,
    WIN_DIAGONAL
};

typedef enum {
    PLAYER_X = -10,
    PLAYER_O = 10,
    DRAW = 0,
    ONGOING
} GameState;

struct Move {
    int player;
    int move;
    struct Move* next;
};

typedef struct Move Move;

void initializeBoard(char board[3][3]);
void displayBoard(char board[3][3]);

enum MoveStatus isMoveValid(char board[3][3], int move);
enum BoardStatus isBoardFull(char board[3][3]);

enum WinStatus checkWin(char board[3][3], char symbol);

void addMove(int player, int move);
void undoLastMove(char board[3][3]);

void multiplayerMode();
void singlePlayerMode();

#endif // GAME_H
