#ifndef HEADERFILE_H
#define HEADERFILE_H

typedef struct nodeCongklak {
	char namaLubang;
	char pemilikLubang;
	int jumlahbiji;
	struct nodeCongklak *berikut;
	struct nodeCongklak *seberang;
	struct nodeLumbung *lumbung;
} nodeCongklak;

typedef struct nodeLumbung {
	char namaLumbung;
	char pemilikLumbung;
	int jumlahbiji;
	struct nodeCongklak *berikut;
} nodeLumbung;

void makeBoard (nodeCongklak *board);
void displayBoard(nodeCongklak *board);


#endif
