#include "Board.h"
#include "Piece.h"
#include <string>
#include<iostream>
#include<fstream>

using namespace std;


Board::Board(int _m, int _n)
{
	m = _m;
	n = _n;
	board = new Piece ***[m];
	for (int i = 0; i < m; i++) {
		board[i] = new Piece**[n];
		for (int j = 0; j < n; j++) {
			board[i][j] = new Piece*[2];
		}
	}
}


Piece::PieceType getPieceTypeFromChar(char piece) {
	switch (piece) {
	case 'R':
		return Piece::PieceType::Rock;
	case 'S':
		return Piece::PieceType::Scissors;
	case 'P':
		return Piece::PieceType::Papper;
	case 'B':
		return Piece::PieceType::Bomb;
	case 'F':
		return Piece::PieceType::Flag;
	}
}

bool Board::AddPiece(Piece piece) {
	if (piece.getX() > m - 1) {
		return false;
	}
	if (piece.getY() > n - 1) {
		return false;
	}

	if (!piece.isJoker()) {
		switch (piece.getType()) {
		case Piece::PieceType::Rock:
				if (maxR < ++totalR) {
					return false;
				}
				break;
		case Piece::PieceType::Papper:
				if (maxP < ++totalP) {
					return false;
				}
				break;
		case Piece::PieceType::Scissors:
				if (maxS < ++totalS) {
					return false;
				}
				break;
		case Piece::PieceType::Flag:
				if (maxF < ++totalF) {
					return false;
				}
				break;
		case Piece::PieceType::Bomb:
				if (maxB < ++totalB) {
					return false;
				}
				break;
			}
	}
	else {
		if (maxJ < ++totalJ) {
			return false;
		}
	}

	board[piece.getY()][piece.getX()][piece.getPlayer() - 1] = &piece;
	return true;
}

void Board::MovePiece(int fromX, int fromY, int toX, int toY, int player) {
	Piece *pieceToMove = board[fromX][fromY][player - 1];
	board[fromX][fromY][player - 1] = nullptr;
	board[toX][toY][player - 1] = pieceToMove;
}
void Board::MovePiece(int fromX, int fromY, int toX, int toY, int player, Piece::PieceType changeJokerType) {
	MovePiece(fromX, fromY, toX, toY, player);
	
	Piece *pieceToMove = board[fromX][fromY][player - 1];
	if ((*pieceToMove).isJoker()) {
		(*pieceToMove).setType(changeJokerType);
	}
}

bool Board::loadPlayer(ifstream& player)
{
	int x, y;
	bool joker;
	bool feof = false;
	Piece::PieceType pt;
	char line[10];
	while (!feof) {
		player.getline(line, 10);
		if (player.eof()) {
			feof = true;
		}
		if (!(line[0] == 'R' || line[0] == 'S' || line[0] == 'P' || line[0] == 'J' || line[0] == 'B' || line[0] == 'F')) { //check the first letter of the input
			return false;
		}
		if (line[0] == 'J') {
			joker = true;
			pt = getPieceTypeFromChar(line[6]);
		}
		else {
			joker = false;
			pt = getPieceTypeFromChar(line[0]);
		}
		x = line[2] - '0';
		y = line[4] - '0';
		Piece *soldier = new Piece(pt, joker, x, y, 1);
		if (!AddPiece(*soldier))
			return false;
	}
	player.close();
	totalR = 0, totalP = 0, totalS = 0, totalF = 0, totalJ = 0, totalB = 0;
	return true;
}


bool Board::initBoard()
{
	//read file of player a
	ifstream player1File("player1.rps_board");
	ifstream player2File("player2.rps_board");
	return loadPlayer(player1File) && loadPlayer(player2File);
}

void printLine() {
	for (int i = 0; i < 10; i++) {
		cout << "--------";
	}
	cout << endl;
}

bool Board::printBoard(string mode, int delay)
{
	if (mode.compare("quiet") != 0) {
		int i, j;
		for (i = 0; i < 10; i++) {
			printLine();
			cout << "|";
			for (j = 0; j < 10; j++) {
				printSquare(i, j, mode);
			}
		}
	}
	return 0;
}

void Board::printSquare(int i, int j, string mode) {
	if (mode.compare("show 1") == 0) {

	}
	else if (mode.compare("show 2") == 0) {
	}
	else {

	}
}

Board::~Board()
{
	for (int i = 0; i < m; i++)
		delete []board[i];
	delete []board;
}
