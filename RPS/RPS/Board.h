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
	void goToXY(const int x, const int y);
	string message = "";
	int winner=-1;
	void printSquare(int i, int j, string mode);
	void printSquare(int i, int j, ofstream& outfile);
	bool Board::checkInitBoard(const bool& initfile1, const int& lineNumber1, const bool& initfile2, const int& lineNumber2);
	bool Board::checkMaxTools(Player* player, const Piece::PieceType& p);
	void Board::setOppositeWinner(const int& player);
	Piece* Board::movePieceCheck(Move* move);
	bool Board::moveJockerPieceCheck(Move* move);
public:
	Board(int m, int n);
	bool loadPlayer(ifstream& player, int playerNum, int& lineNum);
	bool AddPiece(Piece& piece);
	bool MovePiece(Move* move);
	bool initBoard();
	void printBoard(ofstream& outfile);
	void printBoard(std::string mode, int delay);
	string getMessage();
	void setMessage(string _message) { message = _message; }
	int getWinner();
	void setWinner(int player) {
		winner = player;
	}
	bool scanBoard();
	~Board();
};

