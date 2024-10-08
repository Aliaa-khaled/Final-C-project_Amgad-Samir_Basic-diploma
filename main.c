#include <stdio.h>
#include "game.h"

int main() {
    int Gamechoice;

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Select mode:\n");
    printf("1. Multiplayer Mode\n");
    printf("2. Single Player Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &Gamechoice);
    system("cls");
    switch(Gamechoice) {
        case 1:
            printf(">>>> IF YOU WANT TO EXIT AT ANY TIME ENTER (Q/q) <<<<\n");
            multiplayerMode();
            break;
        case 2:
            printf(">>>> IF YOU WANT TO EXIT AT ANY TIME ENTER (Q/q) <<<<\n");
            singlePlayerMode();
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            return 0;
    }
     char playAgain;
     do {
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);
        playAgain = tolower(playAgain);

        if (playAgain == 'y') {
            main();
        } else if (playAgain == 'n') {
            printf("Thank you for playing!\n");
        } else {
            printf("Invalid choice! Please enter 'y' or 'n'.\n");
        }
    } while (playAgain != 'y' && playAgain != 'n');

    return 0;
}
