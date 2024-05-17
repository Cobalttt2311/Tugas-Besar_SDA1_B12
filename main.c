#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "headerfile.h"

int main() {
    int pil;
    nodeCongklak board[14];
    char pilihan;
    int boardInitialized = 0;
    char player1[50], player2[50];
    char *currentPlayer;
    char choice;
    bool game_over = false;

    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("|           GAME CONGKLAK               |\n");
        printf("|---------------------------------------|\n");
        printf("|1. Mulai Permainan                     |\n");
        printf("|2. Tampilkan Skor                      |\n");
        printf("|3. Cara Bermain                        |\n");
        printf("|4. Keluar Permainan                    |\n");
        printf("|                                       |\n");
        printf("=========================================\n");
        printf("Masukan Pilihan Anda (1-4) :\n");
        scanf("%d", &pil);
        getchar(); // Clear the newline character from the input buffer

        switch (pil) {
            case 1:
                system("cls");
                printf("Masukkan Username Player1 : ");
                fgets(player1, sizeof(player1), stdin);
                strtok(player1, "\n"); // Remove newline character from the end of string

                printf("Masukkan Username Player2: ");
                fgets(player2, sizeof(player2), stdin);
                strtok(player2, "\n"); // Remove newline character from the end of string

                currentPlayer = player1;
                system("cls");
                if (!boardInitialized) {
                    makeBoard(board);
                    boardInitialized = 1;
                }

                while (!game_over) {
                    displayBoard(board);
                    printf("%s, pilih lubang (A-N) atau X untuk keluar: ", currentPlayer);
                    scanf(" %c", &choice);
                    choice = toupper(choice); // Convert to uppercase to make it case insensitive

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
                    } else {
                        system("cls");
                        printf("Langkah tidak valid, coba lagi.\n");
                    }

                    // Tambahkan kondisi untuk memeriksa pemenang atau akhir permainan
                    // ...
                }
                break;

            case 2:
                system("cls");
                printf("Masih dalam pengembangan\n");
                break;

            case 3:
                system("cls");
                printf("Masih dalam pengembangan\n");
                break;

            case 4:
                printf("Keluar dari permainan....\n");
                // No need to free the static array
                return 0;

            default:
                printf("Pilihan tidak valid. Silakan masukkan pilihan antara 1-4.\n");
                break;
        }
        printf("Press any key to continue...\n");
        getchar();
    }

    return 0;
}
