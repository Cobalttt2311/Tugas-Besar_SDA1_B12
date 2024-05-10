#ifndef HEADERFILE_H
#define HEADERFILE_H

// Struktur data untuk lubang dalam permainan congklak
typedef struct nodeCongklak {
    char namaLubang;               // Nama lubang
    char pemilikLubang;            // Pemain yang memiliki lubang ('A' atau 'B')
    int jumlahbiji;                // Jumlah biji di dalam lubang
    struct nodeCongklak *berikut;  // Pointer ke lubang berikutnya
    struct nodeCongklak *seberang; // Pointer ke lubang seberang
    struct nodeLumbung *lumbung;   // Pointer ke lumbung yang terhubung
} nodeCongklak;

// Struktur data untuk lumbung dalam permainan congklak
typedef struct nodeLumbung {
    char namaLumbung;               // Nama lumbung
    char pemilikLumbung;           // Pemain yang memiliki lumbung ('A' atau 'B')
    int jumlahbiji;                // Jumlah biji di dalam lumbung
    struct nodeCongklak *berikut;  // Pointer ke lumbung berikutnya
} nodeLumbung;

// Fungsi untuk menginisialisasi papan permainan congklak
void makeBoard(nodeCongklak *board);

// Fungsi untuk menampilkan papan permainan congklak
void displayBoard(nodeCongklak *board);

// Fungsi untuk memindahkan biji dari lubang yang dipilih oleh pemain
void moveSeed(nodeCongklak *board, char lubang);

// Fungsi untuk memeriksa apakah terdapat pemenang dalam permainan congklak
int checkWinner(nodeCongklak *board);

// Fungsi untuk memeriksa apakah langkah yang dipilih oleh pemain adalah langkah yang valid
int isValidMove(nodeCongklak *board, char lubang);

// Fungsi untuk menangkap biji-biji lawan setelah pemain mengakhiri gilirannya di lubang yang berisi satu biji
void captureSeeds(nodeCongklak *board, char lubang);

// Fungsi untuk memeriksa apakah sisi pemain (A atau B) sudah kosong atau tidak memiliki biji
int checkEmptySide(nodeCongklak *board, char pemain);

// Fungsi untuk membatalkan langkah yang telah dilakukan oleh pemain
void undoMove(nodeCongklak *board);

// Fungsi untuk menentukan langkah yang akan diambil oleh komputer sebagai pemain AI
void AI_Move(nodeCongklak *board);

// Fungsi untuk menyimpan status permainan ke dalam file eksternal
void saveGame(nodeCongklak *board, char *filename);

// Fungsi untuk memuat status permainan dari file eksternal
void loadGame(nodeCongklak *board, char *filename);

// Fungsi untuk menampilkan petunjuk cara bermain congklak ke layar
void displayInstructions();

// Fungsi untuk menampilkan menu permainan congklak ke layar
void displayMenu();

#endif
