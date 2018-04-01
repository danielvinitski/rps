#include "Piece.h"



Piece::Piece(PieceType type, bool isJoker, int x, int y, int player)
{
	type = type;
	joker = isJoker;
	x = x;
	y = y;
	player = player;
}


Piece::~Piece()
{
}

int Piece::getX() {
	return x;
}
int Piece::getY() {
	return y;
}
Piece::PieceType Piece::getType() {
	return type;
}
bool Piece::isJoker() {
	return joker;
}