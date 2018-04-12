#include "Move.h"
#include "Board.h"

#pragma once
class Game
{
	Move* getMove(int _plyer, string line);
	Board* gameBoard;

public:
	Game();
	~Game();
	void generateOutput();
	void start(int N, int M, int delay, string mode);
};

