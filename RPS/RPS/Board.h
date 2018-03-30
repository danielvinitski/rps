#include "Piece.h"

#pragma once
class Board
{
	int m, n;
	Piece ***board;

public:
	Board(int m, int n);
	bool AddPiece(Piece piece);
	~Board();
	
};

