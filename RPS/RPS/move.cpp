#include "Move.h"


Move::Move(int _player, int curX, int curY, int tarX, int tarY, bool j)
{
	currentX = curX-1;
	currentY = curY-1;
	targetX = tarX -1;
	targetY = tarY -1;
	joker = j;
	player = _player;
}

Move::Move(int _player, int curX, int curY, int tarX, int tarY, bool j, int jX, int jY, char newType)
{
	currentX = curX -1;
	currentY = curY -1;
	targetX = tarX -1;
	targetY = tarY -1;
	joker = j;
	jokerX = jX -1;
	jokerY = jY -1;
	newPieceType = newType;
	player = _player;
}


Move::~Move()
{
}
