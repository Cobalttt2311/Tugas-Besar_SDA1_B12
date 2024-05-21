#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "headerfile.h"

int main() {
    int pil;
    nodeCongklak board[14];
    char pilihan;
    int boardInitialized = 0;
    char player1[50], player2[50];
    char *currentPlayer;
    char choice;
    bool game_over;
    char input[10];  // buffer for user input

    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("|           GAME CONGKLAK               |\n");
        printf("|---------------------------------------|\n");
        printf("|1. Start Game                          |\n");
        printf("|2. Show Score                          |\n");
        printf("|3. How to play                         |\n");
        printf("|4. Exit                                |\n");
        printf("|                                       |\n");
        printf("=========================================\n");
        printf("Masukan Pilihan Anda (1-4) :\n");
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &pil) != 1 || pil < 1 || pil > 4) {
            printf("Pilihan tidak valid. Silakan masukkan pilihan antara 1-4.\n");
            printf("Press any key to continue...\n");
            getchar();
            continue;
        }

        switch (pil) {
            case 1:
                system("cls");
                printf("Masukkan Username Player1 : ");
                fgets(player1, sizeof(player1), stdin);
                strtok(player1, "\n");

                printf("Masukkan Username Player2 : ");
                fgets(player2, sizeof(player2), stdin);
                strtok(player2, "\n");

                currentPlayer = player1;
                game_over = false;
                system("cls");
                if (!boardInitialized) {
                    makeBoard(board);
                    boardInitialized = 1;
                }

                while (!game_over) {
                    displayBoard(board, player1, player2);
                    printf("%s, pilih lubang (A-N) atau X untuk keluar: ", currentPlayer);
                    scanf(" %c", &choice);
                    choice = toupper(choice);

                    if (choice == 'X') {
                        printf("Permainan berakhir. Terima kasih telah bermain!\n");
                        game_over = true;
                    } else if (choice < 'A' || choice > 'N') {
                        system("cls");
                        printf("Karakter tidak valid. Pilih lubang (A-N).\n");
                    } else if (isValidMove(board, choice, currentPlayer == player1 ? 'A' : 'B')) {
                        moveSeed(board, choice, currentPlayer == player1 ? 'A' : 'B');
                        currentPlayer = (currentPlayer == player1) ? player2 : player1;
                        system("cls");

                        if (checkEmptySide(board, currentPlayer == player1 ? 'A' : 'B')) {
                            printf("Sisi %s kosong. Permainan Berakhir\n", currentPlayer);
                            game_over = true;
                        }

                        int winner = checkWinner(board);
                        if (winner) {
                            system("cls");
                            const char *winnerName = winner == 1 ? player1 : player2;
                            printf("Pemenang adalah %s!\n", winnerName);
                            saveScore("skor.txt", winnerName);
                            printf("Press any key to continue...\n");
                            getchar();
                            game_over = true;
                        }
                    } else {
                        system("cls");
                        printf("Langkah tidak valid, coba lagi.\n");
                    }
                }
                break;

            case 2:
                system("cls");
                displayScores("skor.txt");
                break;

            case 3:
                system("cls");
                FILE *tutorialFile;
                tutorialFile = fopen("tutorial.txt", "r");

                if (tutorialFile == NULL) {
                    printf("File tutorial tidak dapat dibuka.\n");
                } else {
                    printf("Tutorial:\n");
                    char line[256];
                    while (fgets(line, sizeof(line), tutorialFile) != NULL) {
                        printf("%s", line);
                    }
                    fclose(tutorialFile);
                }
                break;

            case 4:
                printf("Keluar dari permainan....\n");
                return 0;

            default:
                // This should never happen due to the input validation
                break;
        }
        printf("Press any key to continue...\n");
        getchar();
    }

    return 0;
}
