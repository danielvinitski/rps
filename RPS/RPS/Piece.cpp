#include "Piece.h"
#include "Player.h"



Piece::Piece(PieceType type_, bool isJoker_, int x_, int y_, Player*& player_, bool isRevealed_)
{
	type = type_;
	joker = isJoker_;
	revealed = isRevealed_;
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
Player* Piece::getPlayer() {
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
bool Piece::isRevealed() {
	return revealed;
}