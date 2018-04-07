#include "Move.h"


Move::Move(int _player, char curX, char curY, char tarX, char tarY, bool j)
{
	currentX = curX - '0';
	currentY = curY - '0';
	targetX = tarX - '0';
	targetY = tarY - '0';
	joker = j;
	player = _player;
}

Move::Move(int _player, char curX, char curY, char tarX, char tarY, bool j, char jX, char jY, char newType)
{
	currentX = curX - '0';
	currentY = curY - '0';
	targetX = tarX - '0';
	targetY = tarY - '0';
	joker = j;
	jokerX = jX - '0';
	jokerY = jY - '0';
	newPieceType = newType;
	player = _player;
}


Move::~Move()
{
}
