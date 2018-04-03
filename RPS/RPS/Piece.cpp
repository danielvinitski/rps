#include "Piece.h"



Piece::Piece(PieceType type_, bool isJoker_, int x_, int y_, int player_)
{
	type = type_;
	joker = isJoker_;
	x = x_;
	y = y_;
	player = player_;
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