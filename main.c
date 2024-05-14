#include <stdio.h>
#include <stdlib.h>
#include "congklak.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
    nodeCongklak board[14];
    char pilihan;
    makeBoard(board);

    while (1) {
        displayBoard(board);
        printf("Pilih lubang (A-N) atau X untuk keluar: ");
        scanf(" %c", &pilihan);

        if (pilihan == 'X' || pilihan == 'x') {
            break;
        }

        moveSeed(board, pilihan);
    }

    return 0;
}
