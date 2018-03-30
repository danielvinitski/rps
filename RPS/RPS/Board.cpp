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
	if (piece.getX() > m - 1) {
		return false;
	}
	if (piece.getY() > n - 1) {
		return false;
	}


	switch (piece.getType()) {
	case 'R':
		if (maxR < ++totalR) {
			return false;
		}
	case 'P':
		if (maxP < ++totalP) {
			return false;
		}
	case 'S':
		if (maxS < ++totalS) {
			return false;
		}
	case 'J':
		if (maxJ < ++totalJ) {
			return false;
		}
	case 'F':
		if (maxF < ++totalF) {
			return false;
		}
	case 'B':
		if (maxB < ++totalB) {
			return false;
		}
	}

	board[m][n] = &piece;
	return true;
}

Board::~Board()
{
	for (int i = 0; i < m; i++)
		delete []board[i];
	delete []board;
}
