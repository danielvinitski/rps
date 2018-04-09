#include "Move.h"


Move::Move(int _player, char curX, char curY, char tarX, char tarY, bool j)
{
	currentX = (curX - '0')-1;
	currentY = (curY - '0')-1;
	targetX = (tarX - '0')-1;
	targetY = (tarY - '0')-1;
	joker = j;
	player = _player;
}

Move::Move(int _player, char curX, char curY, char tarX, char tarY, bool j, char jX, char jY, char newType)
{
	currentX = (curX - '0')-1;
	currentY = (curY - '0')-1;
	targetX = (tarX - '0')-1;
	targetY = (tarY - '0')-1;
	joker = j;
	jokerX = (jX - '0')-1;
	jokerY = (jY - '0')-1;
	newPieceType = newType;
	player = _player;
}


Move::~Move()
{
}
