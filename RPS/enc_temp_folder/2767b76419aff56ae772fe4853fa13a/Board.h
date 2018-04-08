#include "Piece.h"
#include <string>
#include "Move.h"
using namespace std;

#pragma once
class Board
{
	int m, n;
	const int maxR = 2, maxP = 5, maxS = 1, maxF = 1, maxJ = 2, maxB = 2;
	Piece ****board;
	void combat(int x, int y);
	void removePiece(int x, int y, Piece* piece);
	int checkForWinner(Player* player1, Player* player2);
	string message = "";
	int winner=NULL;

public:
	Board(int m, int n);
	bool loadPlayer(ifstream& player, int playerNum, int& lineNum);
	bool AddPiece(Piece& piece);
	bool MovePiece(Move* move);
	bool initBoard();
	void printBoard(std::string mode, int delay);
	void printSquare(int i, int j, string mode);
	string getMessage();
	void setMessage(string _message) { message = _message; }
	int getWinner();
	void setWinner(int player) {
		winner = player;
	}
	bool scanBoard();
	~Board();
};

