#include <stdio.h>
#include "game.h"

int main() {
    int choice;

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Select mode:\n");
    printf("1. Multiplayer Mode\n");
    printf("2. Single Player Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            multiplayerMode();
            break;
        case 2:
            singlePlayerMode();
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            return 1;
    }

    return 0;
}
