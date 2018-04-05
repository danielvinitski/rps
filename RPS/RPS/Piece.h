#include "Player.h"

#pragma once
class Piece
{
public:
	enum PieceType { Rock = 'R', Papper = 'P', Scissors = 'S', Bomb = 'B', Flag='F' };
	Piece(PieceType type, bool isJoker, int x, int y, Player*& player, bool isRevealed);
	int getX();
	int getY();
	Player* getPlayer();
	bool isJoker();
	bool isRevealed();
	PieceType getType();
	void Piece::setType(Piece::PieceType newType);
	bool Piece::getRevealed();
	void Piece::setRevealed(bool b);
	~Piece();

private:
	PieceType type;
	int x, y;
	Player *player;
	bool joker;
	bool revealed;
};

