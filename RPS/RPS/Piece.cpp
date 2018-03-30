#include "Piece.h"



Piece::Piece(PieceType type, bool isJoker, int x, int y, int player)
{
	type = type;
	isJoker = isJoker;
	x = x;
	y = y;
	player = player;
}


Piece::~Piece()
{
}
