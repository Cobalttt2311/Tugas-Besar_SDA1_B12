#include <stdio.h>
#include <stdlib.h>
#include "headerfile.h"

int main() {
    int pil;
    nodeCongklak board[14];
    char pilihan;
    int boardInitialized = 0;

    while (1) {
        system("cls"); // Clear the console screen
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

        switch (pil) {
            case 1:
                system("cls");
                if (!boardInitialized) {
                    makeBoard(board);
                    boardInitialized = 1;
                }
                
                while (1) {
                    displayBoard(board);
                    printf("Pilih lubang (A-N) atau X untuk keluar: ");
                    scanf(" %c", &pilihan);

                    if (pilihan == 'X' || pilihan == 'x') {
                        break;
                    }

                    moveSeed(board, pilihan);
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
        getchar(); 
    }

    return 0;
}
