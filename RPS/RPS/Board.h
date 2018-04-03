#include "Piece.h"
#include <string>
using namespace std;

#pragma once
class Board
{
	int m, n;
	const int maxR = 2, maxP = 5, maxS = 1, maxF = 1, maxJ = 2, maxB=2;
	int totalR = 0, totalP = 0, totalS = 0, totalF = 0, totalJ = 0, totalB=0;
	Piece ****board;

public:
	Board(int m, int n);
	bool loadPlayer(ifstream& player, int playerNum);
	bool AddPiece(Piece& piece);
	void MovePiece(int fromX, int fromY, int toX, int toY, int player);
	void MovePiece(int fromX, int fromY, int toX, int toY, int player, Piece::PieceType changeJokerType);
	bool initBoard();
	bool printBoard(std::string mode, int delay);
	void printSquare(int i, int j, string mode);
	~Board();
};

