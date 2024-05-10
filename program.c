#include <stdio.h>
#include <stdlib.h>
#include "headerfile.h"

// Fungsi untuk menginisialisasi papan permainan congklak
void makeBoard(nodeCongklak *board) {
    nodeCongklak *current = board;
    nodeLumbung *lumbungA = NULL;
    nodeLumbung *lumbungB = NULL;
    char lubang;

    // Inisialisasi lubang untuk pemain A
    for (lubang = 'A'; lubang <= 'G'; lubang++) {
        current->namaLubang = lubang;
        current->pemilikLubang = 'A';
        current->jumlahbiji = 4; // Misalnya, awalnya setiap lubang memiliki 4 biji
        current->berikut = (nodeCongklak *)malloc(sizeof(nodeCongklak));
        current->seberang = NULL; // Lubang belum terhubung ke lubang seberang
        current->lumbung = NULL;  // Lubang tidak memiliki lumbung
        current = current->berikut;
    }

    // Inisialisasi lubang untuk pemain B
    for (lubang = 'H'; lubang <= 'N'; lubang++) {
        current->namaLubang = lubang;
        current->pemilikLubang = 'B';
        current->jumlahbiji = 4; // Misalnya, awalnya setiap lubang memiliki 4 biji
        current->berikut = (nodeCongklak *)malloc(sizeof(nodeCongklak));
        current->seberang = NULL; // Lubang belum terhubung ke lubang seberang
        current->lumbung = NULL;  // Lubang tidak memiliki lumbung
        current = current->berikut;
    }

    // Inisialisasi lumbung A
    lumbungA = (nodeLumbung *)malloc(sizeof(nodeLumbung));
    lumbungA->namaLumbung = 'A';
    lumbungA->pemilikLumbung = 'A';
    lumbungA->jumlahbiji = 0;
    lumbungA->berikut = NULL;

    // Inisialisasi lumbung B
    lumbungB = (nodeLumbung *)malloc(sizeof(nodeLumbung));
    lumbungB->namaLumbung = 'B';
    lumbungB->pemilikLumbung = 'B';
    lumbungB->jumlahbiji = 0;
    lumbungB->berikut = NULL;

    // Menghubungkan lubang-lubang dengan lubang seberang
    current = board;
    for (lubang = 'A'; lubang <= 'N'; lubang++) {
        if (lubang == 'A' || lubang == 'B' || lubang == 'C' || lubang == 'D' || lubang == 'E' || lubang == 'F' || lubang == 'G') {
            current->seberang = board + ('H' - lubang);
        } else {
            current->seberang = board + ('A' - lubang);
        }
        current = current->berikut;
    }

    // Menghubungkan lubang-lubang dengan lumbung masing-masing pemain
    current = board;
    while (current->namaLubang != 'A') {
        current = current->berikut;
    }
    current->lumbung = lumbungA;

    while (current->namaLubang != 'H') {
        current = current->berikut;
    }
    current->lumbung = lumbungB;
}

// Fungsi untuk menampilkan papan permainan congklak
void displayBoard(nodeCongklak *board) {
    nodeCongklak *current = board;
    char lubang;

    printf("Papan Permainan Congklak:\n");

    // Menampilkan lubang-lubang untuk pemain A
    printf("Pemain A: ");
    for (lubang = 'A'; lubang <= 'G'; lubang++) {
        printf("[%c: %d] ", current->namaLubang, current->jumlahbiji);
        current = current->berikut;
    }
    printf("\n");

    // Menampilkan lubang-lubang untuk pemain B
    printf("Pemain B: ");
    while (current != NULL && current->namaLubang != 'H') {
        current = current->berikut;
    }
    for (lubang = 'H'; lubang <= 'N'; lubang++) {
        printf("[%c: %d] ", current->namaLubang, current->jumlahbiji);
        current = current->berikut;
    }
    printf("\n");

    // Menampilkan lumbung pemain A
    printf("Lumbung A: [Lumbung A: %d]\n", board->lumbung->jumlahbiji);

    // Menampilkan lumbung pemain B
    nodeLumbung *lumbungB = board->lumbung->berikut;
    printf("Lumbung B: [Lumbung B: %d]\n", lumbungB->jumlahbiji);
}




