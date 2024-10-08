#include <stdio.h>
#include <ctype.h>
#include "game.h"

void multiplayerMode() {
    char board[3][3];
    int currentPlayer = 1;
    char move;
    char symbolPlayer1, symbolPlayer2;

    initializeBoard(board);

    do {
        printf("Choose your symbol (X or O): ");
        scanf(" %c", &symbolPlayer1);
        symbolPlayer1 = toupper(symbolPlayer1);

        if (symbolPlayer1 == 'X') {
            symbolPlayer2 = 'O';
        } else if (symbolPlayer1 == 'O') {
            symbolPlayer2 = 'X';
        } else if (symbolPlayer1 == 'Q' || symbolPlayer1 == 'q') {
            printf("You chose to quit the game. Exiting...\n");
            return;
        } else {
            printf("Invalid choice. Please choose X or O.\n");
        }
    } while (symbolPlayer1 != 'X' && symbolPlayer1 != 'O');

    while (true) {
        displayBoard(board);

        printf("Player %d's turn (%c):\n", currentPlayer, (currentPlayer == 1) ? symbolPlayer1 : symbolPlayer2);
        printf("Enter your move (1-9) or 'q' to quit: ");
        scanf(" %c", &move);

        if (move == 'q' || move == 'Q') {
            printf("You chose to quit the game. Exiting...\n");
            return;
        }

        if (isMoveValid(board, move - '0') != MOVE_VALID) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        int row = (move - '1') / 3;
        int col = (move - '1') % 3;
        board[row][col] = (currentPlayer == 1) ? symbolPlayer1 : symbolPlayer2;

        addMove(currentPlayer, move - '0');

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
