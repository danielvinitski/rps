#include "Piece.h"
#include <string>
using namespace std;

#pragma once
class Board
{
	int m, n;
	const int maxR = 2, maxP = 5, maxS = 1, maxF = 1, maxJ = 2, maxB=2;
	Piece ****board;
	void combat(int x, int y);
	void removePiece(int x, int y, Piece* piece);
	Player* checkForWinner(Player* player1, Player* player2);

public:
	Board(int m, int n);
	bool loadPlayer(ifstream& player, int playerNum);
	bool AddPiece(Piece& piece);
	void MovePiece(int fromX, int fromY, int toX, int toY, int player);
	void MovePiece(int fromX, int fromY, int toX, int toY, int player, Piece::PieceType changeJokerType);
	bool initBoard();
	bool printBoard(std::string mode, int delay);
	void printSquare(int i, int j, string mode);
	Player* scanBoard();
	~Board();
};

