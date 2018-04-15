#include "Move.h"
#include "Board.h"

#pragma once
class Game
{
	Move* getMove(const int _plyer, string line);
	Board* gameBoard;
	void Game::generateOutput(Board& board);
	bool playMove(const int& player, int& fileLineCounter, ifstream& playerMoveFile, Board& board, const int& delay, const string& mode);
	Move* Game::setMove(const string* moveList, const int& player);
	void Game::playGame(Board& board, const int& delay, const string& mode);
	bool Game::checkMove(const int& curX, const int& curY, const int& tarX, const int& tarY, const bool& joker, const int& jX, const int& jY, const char& newType);
public:
	Game();
	~Game();
	
	void start(int N, int M, int delay, string mode);
};

