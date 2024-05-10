#include <stdio.h>
#include <stdlib.h>
#include "headerfile.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	// Membuat papan permainan
    nodeCongklak *board = (nodeCongklak *)malloc(sizeof(nodeCongklak));
    makeBoard(board);

    // Menampilkan papan permainan
    displayBoard(board);

    // Dealokasi memori papan permainan
    free(board);

    return 0;
}
