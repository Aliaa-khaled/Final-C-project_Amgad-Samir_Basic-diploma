#include <stdio.h>
#include "game.h"

void multiplayerMode() {
    char board[3][3];
    int currentPlayer = 1;
    int move;
    char symbolPlayer1;

    initializeBoard(board);

    printf("Player 1, choose your symbol (X or O): ");
    scanf(" %c", &symbolPlayer1);
    while (symbolPlayer1 != 'X' && symbolPlayer1 != 'O') {
        printf("Invalid symbol. Choose 'X' or 'O': ");
        scanf(" %c", &symbolPlayer1);
    }

    char symbolPlayer2 = (symbolPlayer1 == 'X') ? 'O' : 'X';

    while (true) {
        displayBoard(board);

        printf("Player %d's turn (%c):\n", currentPlayer, (currentPlayer == 1) ? symbolPlayer1 : symbolPlayer2);
        printf("Enter your move (1-9): ");
        scanf("%d", &move);

        if (isMoveValid(board, move) != MOVE_VALID) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        int row = (move - 1) / 3;
        int col = (move - 1) % 3;
        board[row][col] = (currentPlayer == 1) ? symbolPlayer1 : symbolPlayer2;

        addMove(currentPlayer, move);

        if (checkWin(board, (currentPlayer == 1) ? symbolPlayer1 : symbolPlayer2) != WIN_NONE) {
            displayBoard(board);
            printf("Player %d wins!\n", currentPlayer);
            break;
        }

        if (isBoardFull(board) == BOARD_FULL) {
            displayBoard(board);
            printf("It's a draw!\n");
            break;
        }

        char choice;
        while (true) {
            printf("Player %d, do you want to undo your last move? (y/n): ", currentPlayer);
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                undoLastMove(board);
                continue;
            } else if (choice == 'n' || choice == 'N') {
                break;
            } else {
                printf("Invalid choice! Please enter 'y' or 'n'.\n");
            }
        }

        currentPlayer = (currentPlayer == 1) ? 0 : 1;
    }

}
