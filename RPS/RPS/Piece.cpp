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
int Piece::getPlayer() {
	return player;
}
Piece::PieceType Piece::getType() {
	return type;
}
void Piece::setType(Piece::PieceType newType) {
	type = newType;
}
bool Piece::isJoker() {
	return joker;
}