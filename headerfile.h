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
    nodeLumbung *lumbung;
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

// Fungsi untuk menangkap biji-biji lawan setelah pemain mengakhiri gilirannya di lubang yang berisi satu biji
void captureSeeds(nodeCongklak *board, char lubang);

// Fungsi untuk memeriksa apakah terdapat pemenang dalam permainan congklak
int checkWinner(nodeCongklak *board);

//-----------------------------------------------------------------------------------------------------------------------------------------

// Fungsi untuk menyimpan status permainan ke dalam file eksternal
void saveGame(nodeCongklak *board, const char *filename);

// Fungsi untuk memuat status permainan dari file eksternal
void loadGame(nodeCongklak *board, const char *filename);

// Fungsi untuk menampilkan petunjuk cara bermain congklak ke layar
void displayInstructions();

// Fungsi untuk menampilkan menu permainan congklak ke layar
void displayMenu();

#endif // HEADERFILE_H
