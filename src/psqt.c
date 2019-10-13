// psqt.c

#include "data.h"
#include "types.h"

int PSQT[PIECE_NB][64];


// Initialize the piece square tables with piece values included
static void InitPSQT() __attribute__((constructor));
static void InitPSQT() {
	int tempPSQT[8][64] = {
		{ 0 }, // Unused
		{ // Pawn
		 0,   0,   0,   0,   0,   0,   0,   0,
		20,  20,  20,  30,  30,  20,  20,  20,
		10,  10,  10,  20,  20,  10,  10,  10,
		 5,   5,   5,  10,  10,   5,   5,   5,
		 0,   0,  10,  20,  20,  10,   0,   0,
		 5,   0,   0,   5,   5,   0,   0,   5,
		10,  10,   0, -10, -10,   0,  10,  10,
		 0,   0,   0,   0,   0,   0,   0,   0},

		{ // Knight
		0,   0,   0,   0,   0,   0,   0,   0,
		0,   0,   5,  10,  10,   5,   0,   0,
		5,  10,  10,  20,  20,  10,  10,   5,
		5,  10,  15,  20,  20,  15,  10,   5,
		0,   0,  10,  20,  20,  10,   5,   0,
		0,   0,  10,  10,  10,  10,   0,   0,
		0,   0,   0,   5,   5,   0,   0,   0,
		0, -10,   0,   0,   0,   0, -10,   0},

		{ // Bishop
		0,   0,   0,   0,   0,   0,   0,   0,
		0,   0,   0,  10,  10,   0,   0,   0,
		0,   0,  10,  15,  15,  10,   0,   0,
		0,  10,  15,  20,  20,  15,  10,   0,
		0,  10,  15,  20,  20,  15,  10,   0,
		0,   0,  10,  15,  15,  10,   0,   0,
		0,   0,   0,  10,  10,   0,   0,   0,
		0,   0, -10,   0,   0, -10,   0,   0},

		{ // Rook
         0,   0,   5,  10,  10,   5,   0,   0,
        25,  25,  25,  25,  25,  25,  25,  25,
         0,   0,   5,  10,  10,   5,   0,   0,
         0,   0,   5,  10,  10,   5,   0,   0,
         0,   0,   5,  10,  10,   5,   0,   0,
         0,   0,   5,  10,  10,   5,   0,   0,
         0,   0,   5,  10,  10,   5,   0,   0,
         0,   0,   5,  10,  10,   5,   0,   0},

		{ 0 }, // Queen 

		{ // King early
       -70, -70, -70, -70, -70, -70, -70, -70,
       -70, -70, -70, -70, -70, -70, -70, -70,
       -70, -70, -70, -70, -70, -70, -70, -70,
       -70, -70, -70, -70, -70, -70, -70, -70,
       -70, -70, -70, -70, -70, -70, -70, -70,
       -50, -50, -50, -50, -50, -50, -50, -50,
       -30, -30, -30, -30, -30, -30, -30, -30,
         0,   5,   5, -10, -10,   0,  10,   5},

		{ // King endgame
       -50, -10,   0,   0,   0,   0, -10, -50,
       -10,   0,  10,  10,  10,  10,   0, -10,
         0,  10,  20,  20,  20,  20,  10,   0,
         0,  10,  20,  40,  40,  20,  10,   0,
         0,  10,  20,  40,  40,  20,  10,   0,
         0,  10,  20,  20,  20,  20,  10,   0,
       -10,   0,  10,  10,  10,  10,   0, -10,
       -50, -10,   0,   0,   0,   0, -10, -50}};

	// Black scores are negated (white double negated -> positive)
	for (int piece = bP; piece <= bK; ++piece)
		for (int sq = A1; sq <= H8; ++sq) {
			PSQT[piece][sq] = -(tempPSQT[piece][sq] + pieceValue[piece]);
			PSQT[piece+8][mirror[sq]] = -PSQT[piece][sq];
		}

	// Different PSQT for kings in the endgame
	for (int sq = A1; sq <= H8; ++sq) {
		PSQT[bK+1][sq]         = -tempPSQT[KING+1][sq];
		PSQT[wK+1][mirror[sq]] = -PSQT[bK+1][sq];
	}
}