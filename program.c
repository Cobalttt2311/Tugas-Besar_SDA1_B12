#include <stdio.h>
#include <stdlib.h>
#include "headerfile.h"

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

void displayBoard(nodeCongklak *board, char play1[], char play2[]) {
    int i;

    printf("Papan Permainan Congklak:\n");

    // Menampilkan lumbung pemain A
    printf("=======\n");
    printf("|LA: %d| -----> Lumbung %s\n", board[6].lumbung->jumlahbiji, play1);
    printf("=======\n");

    // Menampilkan lubang-lubang pemain A
    for (i = 0; i < 7; i++) {
        printf("======");
    }
    printf("\n");
    for (i = 0; i < 7; i++) {
        printf("|%c: %d|", board[i].namaLubang, board[i].jumlahbiji);
    }
    printf("\n");
    for (i = 0; i < 7; i++) {
        printf("======");
    }
    printf("\n");

    // Menampilkan lubang-lubang pemain B
    for (i = 13; i >= 7; i--) {
        printf("======");
    }
    printf("\n");
    for (i = 13; i >= 7; i--) {
        printf("|%c: %d|", board[i].namaLubang, board[i].jumlahbiji);
    }
    printf("\n");
    for (i = 13; i >= 7; i--) {
        printf("======");
    }
    printf("\n");

    // Menampilkan lumbung pemain B
    printf("=======\n");
    printf("|LB: %d| -----> Lumbung %s\n", board[13].lumbung->jumlahbiji, play2);
    printf("=======\n");
}

void moveSeed(nodeCongklak *board, char lubangPilih, char player) {
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

    // Mulai penyebaran biji
    while (jumlahBiji > 0) {
        // Pindah ke lubang berikutnya
        current = current->berikut;

        // Jika mencapai lubung lawan, lewati
        if (current == (nodeCongklak *)lumbungPlayer && lumbungPlayer->pemilikLumbung != player) {
            continue;
        }

        // Tambahkan biji ke lubang berikutnya
        current->jumlahbiji++;
        jumlahBiji--;

        // Jika biji terakhir jatuh di lumbung pemain sendiri
        if (jumlahBiji == 0 && current == (nodeCongklak *)lumbungPlayer) {
            break;
        }
    }

    // Jika biji terakhir jatuh di lubang kosong milik pemain sendiri
    if (jumlahBiji == 0 && current != (nodeCongklak *)lumbungPlayer && current->jumlahbiji == 1 && current->pemilikLubang == player) {
        if (current->seberang != NULL) {
            // Ambil semua biji dari lubang seberang dan tambahkan ke lumbung
            nodeCongklak *seberang = current->seberang;
            lumbungPlayer->jumlahbiji += seberang->jumlahbiji + current->jumlahbiji;
            seberang->jumlahbiji = 0;
            current->jumlahbiji = 0;
        }
    }
}


int isValidMove(nodeCongklak *board, char lubang, char player) {
    nodeCongklak *current = board;

    // Cari lubang yang dipilih
    while (current != NULL && current->namaLubang != lubang) {
        current = current->berikut;
    }

    // Jika lubang tidak ditemukan, langkah tidak valid
    if (current == NULL) {
        return 0;
    }

    // Periksa apakah lubang milik pemain yang sedang bermain
    if (current->pemilikLubang != player) {
        return 0;
    }

    // Periksa apakah lubang tidak kosong
    if (current->jumlahbiji == 0) {
        return 0;
    }

    // Jika semua kondisi di atas terpenuhi, langkah valid
    return 1;
}

int checkEmptySide(nodeCongklak *board, char player){
    int i;
    int startIndex = (player == 'A') ? 0 : 7;
    int endIndex = (player == 'A') ? 6 : 13;
    
    for (i = startIndex; i <= endIndex; i++){
        if (board[i].jumlahbiji > 0){
            return 0;
        }
    }
    
    return 1;
}

void captureSeeds(nodeCongklak *board, char lubang) {
    int index = lubang - 'A'; // Hitung indeks lubang yang dipilih
    char player = board[index].pemilikLubang; // Mendapatkan pemilik lubang
    int oppositeIndex = 12 - index; // Hitung indeks lubang seberang

    // Jika lubang yang dipilih milik pemain A, maka seberangnya milik pemain B
    // Jika lubang yang dipilih milik pemain B, maka seberangnya milik pemain A
    char oppositePlayer = (player == 'A') ? 'B' : 'A';

    // Menangkap biji-biji lawan
    if (board[index].jumlahbiji == 1 && board[oppositeIndex].jumlahbiji > 0) {
        // Jika lubang terakhir berisi satu biji dan lubang seberang tidak kosong
        int capturedSeeds = board[oppositeIndex].jumlahbiji; // Ambil jumlah biji di lubang seberang

        // Menambahkan biji-biji lawan ke lumbung pemain yang sedang giliran
        if (player == 'A') {
            board[6].jumlahbiji += capturedSeeds;
        } else {
            board[13].jumlahbiji += capturedSeeds;
        }

        // Menambahkan biji di lubang terakhir (yang di seberang) ke lumbung pemain yang sedang giliran
        board[6 + (player == 'A' ? 1 : 7)].jumlahbiji += board[oppositeIndex].jumlahbiji;

        // Mengosongkan lubang seberang
        board[oppositeIndex].jumlahbiji = 0;
    }
}

