#include <stdio.h>
#include <stdlib.h>
#include "congklak.h"

// Fungsi untuk menginisialisasi papan permainan congklak
void makeBoard(nodeCongklak *board) {
    nodeCongklak *current = board;
    nodeLumbung *lumbungA = NULL;
    nodeLumbung *lumbungB = NULL;
    int i;

    // Inisialisasi lubang untuk pemain A
    for (i = 0; i < 7; i++) {
        current[i].namaLubang = 'A' + i;
        current[i].pemilikLubang = 'A';
        current[i].jumlahbiji = 7; // Misalnya, awalnya setiap lubang memiliki 7 biji
        current[i].berikut = &current[i + 1];
        current[i].seberang = NULL;
        current[i].lumbung = NULL;
    }

    // Inisialisasi lubang untuk pemain B
    for (i = 7; i < 14; i++) {
        current[i].namaLubang = 'H' + (i - 7);
        current[i].pemilikLubang = 'B';
        current[i].jumlahbiji = 7; // Misalnya, awalnya setiap lubang memiliki 7 biji
        if (i < 13) {
            current[i].berikut = &current[i + 1];
        } else {
            current[i].berikut = NULL;
        }
        current[i].seberang = NULL;
        current[i].lumbung = NULL;
    }

    // Inisialisasi lumbung A
    lumbungA = (nodeLumbung *)malloc(sizeof(nodeLumbung));
    lumbungA->namaLumbung = 'A';
    lumbungA->pemilikLumbung = 'A';
    lumbungA->jumlahbiji = 0;
    lumbungA->berikut = &current[7]; // Lumbung A mengarah ke lubang H

    // Inisialisasi lumbung B
    lumbungB = (nodeLumbung *)malloc(sizeof(nodeLumbung));
    lumbungB->namaLumbung = 'B';
    lumbungB->pemilikLumbung = 'B';
    lumbungB->jumlahbiji = 0;
    lumbungB->berikut = &current[0]; // Lumbung B mengarah ke lubang A

    // Menghubungkan lubang-lubang dengan lubang seberang
    for (i = 0; i < 7; i++) {
        current[i].seberang = &current[13 - i];
        current[7 + i].seberang = &current[6 - i];
    }

    // Menghubungkan lubang-lubang dengan lumbung masing-masing pemain
    for (i = 0; i < 7; i++) {
        current[i].lumbung = lumbungA;
        current[7 + i].lumbung = lumbungB;
    }

    // Menghubungkan lubang terakhir ke lumbung masing-masing
    current[6].berikut = (nodeCongklak *)lumbungA;
    current[13].berikut = (nodeCongklak *)lumbungB;
    
    
}

// Fungsi untuk menampilkan papan permainan congklak
void displayBoard(nodeCongklak *board) {
    int i;

    printf("Papan Permainan Congklak:\n");

    // Menampilkan lubang-lubang untuk pemain A
    printf("Pemain A: ");
    for (i = 0; i < 7; i++) {
        printf("[%c: %d] ", board[i].namaLubang, board[i].jumlahbiji);
    }
    printf("\n");

    // Menampilkan lubang-lubang untuk pemain B
    printf("Pemain B: ");
    for (i = 7; i < 14; i++) {
        printf("[%c: %d] ", board[i].namaLubang, board[i].jumlahbiji);
    }
    printf("\n");

    // Menampilkan lumbung pemain A
    printf("Lumbung A: [Jumlah Biji: %d]\n", board[6].lumbung->jumlahbiji);

    // Menampilkan lumbung pemain B
    printf("Lumbung B: [Jumlah Biji: %d]\n", ((nodeLumbung *)board[13].lumbung)->jumlahbiji);
}

void moveSeed(nodeCongklak *board, char lubangPilih) {
    nodeCongklak *current = board;
    nodeLumbung *lumbungPlayer = NULL;
    int jumlahBiji;

    // Cari lubang yang dipilih
    while (current != NULL && current->namaLubang != lubangPilih) {
        current = current->berikut;
    }

    if (current == NULL) {
        printf("Lubang tidak ditemukan!\n");
        return;
    }

    if (current->jumlahbiji == 0) {
        printf("Lubang kosong, pilih lubang lain!\n");
        return;
    }

    // Ambil jumlah biji dari lubang yang dipilih
    jumlahBiji = current->jumlahbiji;
    current->jumlahbiji = 0;

    // Tentukan lumbung pemain
    lumbungPlayer = current->lumbung;

    while (jumlahBiji > 0) {
        // Pindah ke lubang berikutnya
        current = current->berikut;

        // Jika mencapai akhir, mulai dari awal
        if (current == NULL) {
            current = board;
        }

        // Jika mencapai lumbung milik sendiri, tambahkan biji
        if (current == (nodeCongklak *)lumbungPlayer) {
            lumbungPlayer->jumlahbiji++;
            jumlahBiji--;
        } else if (current != (nodeCongklak *)lumbungPlayer->berikut) {
            // Tambahkan biji ke lubang berikutnya jika bukan lumbung lawan
            current->jumlahbiji++;
            jumlahBiji--;
        }
    }

    // Jika biji terakhir jatuh di lubang kosong milik pemain sendiri
    if (current != (nodeCongklak *)lumbungPlayer && current->jumlahbiji == 1 && current->pemilikLubang == lubangPilih) {
        if (current->seberang != NULL) {
            // Ambil semua biji dari lubang seberang dan tambahkan ke lumbung
            nodeCongklak *seberang = current->seberang;
            lumbungPlayer->jumlahbiji += seberang->jumlahbiji;
            seberang->jumlahbiji = 0;
        }
    }
}






