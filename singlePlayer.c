#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

extern Move* moveHistory;

void singlePlayerMode() {
    char board[3][3];
    initializeBoard(board);

    char playerSymbol, computerSymbol;
    int currentPlayer;

    do {
        printf("Choose your symbol (X or O): ");
        scanf(" %c", &playerSymbol);
        playerSymbol = toupper(playerSymbol);

        if (playerSymbol == 'X') {
            computerSymbol = 'O';
        } else if (playerSymbol == 'O') {
            computerSymbol = 'X';
        } else if (playerSymbol == 'Q' || playerSymbol == 'q') {
            printf("You chose to quit the game. Exiting...\n");
            return;  // للخروج من اللعبة إذا أدخل اللاعب Q
        } else {
            printf("Invalid choice. Please choose X or O.\n");
        }
    } while (playerSymbol != 'X' && playerSymbol != 'O');

    currentPlayer = 1;
    GameState gameState = ONGOING;

    printf("Welcome to Tic-Tac-Toe!\n");
    displayBoard(board);

    while (gameState == ONGOING)
    {
        if (currentPlayer == 1)
        {
            char move;
            enum MoveStatus moveStatus;

            do
            {
                printf("Enter your move (1-9) or 'q' to quit: ");
                scanf(" %c", &move);

                if (move == 'q' || move == 'Q')
                {
                    printf("You chose to quit the game. Exiting...\n");
                    return;
                }

                if (move >= '1' && move <= '9')
                {
                    moveStatus = isMoveValid(board, move - '0');
                }
                else
                {
                    printf("Invalid input. Please enter a number between 1 and 9 or 'q' to quit.\n");
                    moveStatus = MOVE_OUT_OF_RANGE;
                }

                if (moveStatus == MOVE_OUT_OF_RANGE)
                {
                    printf("Move is out of range. Try again.\n");
                }
                else if (moveStatus == MOVE_SPOT_TAKEN)
                {
                    printf("Spot is already taken. Choose another spot.\n");
                }
            }
            while (moveStatus != MOVE_VALID);

            int row = (move - '1') / 3;
            int col = (move - '1') % 3;
            board[row][col] = playerSymbol;
            addMove(1, move - '0');

            char playerChoice;
            printf("Do you want to undo the last move? (y/n): ");
            scanf(" %c", &playerChoice);

            if (playerChoice == 'y' || playerChoice == 'Y')
            {
                undoLastMove(board);
                displayBoard(board);
                continue;
            }

            currentPlayer = 0;
        }
        else
        {
            printf("Computer (%c)'s turn:\n", computerSymbol);
            computerMove(board, computerSymbol, playerSymbol);
            currentPlayer = 1;
        }
        displayBoard(board);

        enum WinStatus winStatus = checkWin(board, currentPlayer == 0 ? playerSymbol : computerSymbol);
        if (winStatus != WIN_NONE)
        {
            gameState = (currentPlayer == 0) ? PLAYER_O : PLAYER_X;
            break;
        }

        if (isBoardFull(board) == BOARD_FULL)
        {
            gameState = DRAW;
        }
    }

    if (gameState == PLAYER_X)
    {
        printf("Player %c wins!\n", playerSymbol);
    }
    else if (gameState == PLAYER_O)
    {
        printf("Computer %c wins!\n", computerSymbol);
    }
    else if (gameState == DRAW)
    {
        printf("It's a draw!\n");
    }

}

int minimax(char board[3][3], int depth, bool isMax, char computerSymbol, char playerSymbol)
{
    if (checkWin(board, computerSymbol) != WIN_NONE)
    {
        return 10 - depth;
    }

    if (checkWin(board, playerSymbol) != WIN_NONE)
    {
        return depth - 10;
    }

    if (isBoardFull(board) == BOARD_FULL)
    {
        return 0;
    }

    if (isMax)
    {
        int bestVal = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = computerSymbol;
                    int value = minimax(board, depth + 1, false, computerSymbol, playerSymbol);
                    board[i][j] = ' ';
                    bestVal = (value > bestVal) ? value : bestVal;
                }
            }
        }
        return bestVal;
    }
    else
    {
        int bestVal = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = playerSymbol;
                    int value = minimax(board, depth + 1, true, computerSymbol, playerSymbol);
                    board[i][j] = ' ';
                    bestVal = (value < bestVal) ? value : bestVal;
                }
            }
        }
        return bestVal;
    }
}

void computerMove(char board[3][3], char computerSymbol, char playerSymbol)
{
    int bestVal = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = computerSymbol;
                int moveVal = minimax(board, 0, false, computerSymbol, playerSymbol);
                board[i][j] = ' ';

                if (moveVal > bestVal)
                {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestMoveRow][bestMoveCol] = computerSymbol;
    addMove(0, bestMoveRow * 3 + bestMoveCol + 1);
}
