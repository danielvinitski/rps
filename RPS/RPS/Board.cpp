#include "Board.h"
#include "Piece.h"


Board::Board(int m, int n)
{
	m = m;
	n = n;
	board = new Piece **[m];
	for (int i = 0; i < m; i++)
		board[i] = new Piece*[n];
}

bool Board::AddPiece(Piece piece) {
	return true;
}

Board::~Board()
{
	for (int i = 0; i < m; i++)
		delete []board[i];
	delete []board;
}
