#ifndef HEADERFILE_H
#define HEADERFILE_H

typedef struct nodeLumbung {
    char namaLumbung;
    char pemilikLumbung;
    int jumlahbiji;
    struct nodeCongklak *berikut;
} nodeLumbung;

typedef struct nodeCongklak {
    char namaLubang;
    char pemilikLubang;
    int jumlahbiji;
    struct nodeCongklak *berikut;
    struct nodeCongklak *seberang;
    struct nodeLumbung *lumbung;
} nodeCongklak;

// Fungsi untuk membuat papan congklak ( alokasi memori buat congklak )
void makeBoard(nodeCongklak *board);

// Fungsi buat nampilin display congklak
void displayBoard(nodeCongklak *board, char play1[], char play2[]);

// Fungsi untuk menggerakan Biji
void moveSeed(nodeCongklak *board, char lubangPilih, char player);

// Fungsi untuk memeriksa pergerakan biji , apakah benar atau tidak
int isValidMove(nodeCongklak *board, char lubang, char player);

// Fungsi untuk memeriksa sisi yang kosong
int checkEmptySide(nodeCongklak *board, char player);

// Fungsi untuk memeriksa apakah terdapat pemenang dalam permainan congklak
int checkWinner(nodeCongklak *board);

//Inisialisasi nama pemilik lumbung
void initializeLumbung(nodeLumbung *lumbung, char pemilik);

void saveScore(const char *filename, const char *winner);

void displayScores(const char *filename);

//-----------------------------------------------------------------------------------------------------------------------------------------

// Fungsi untuk menyimpan status permainan ke dalam file eksternal
void saveGame(nodeCongklak *board, const char *filename);

// Fungsi untuk memuat status permainan dari file eksternal
void loadGame(nodeCongklak *board, const char *filename);

#endif // HEADERFILE_H
