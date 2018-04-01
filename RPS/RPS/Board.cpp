#include "Board.h"
#include "Piece.h"
#include <string>
#include<iostream>
#include<fstream>

using namespace std;


Board::Board(int m, int n)
{
	m = m;
	n = n;
	board = new Piece **[m];
	for (int i = 0; i < m; i++)
		board[i] = new Piece*[n];
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
		case 'R':
			if (maxR < ++totalR) {
				return false;
			}
		case 'P':
			if (maxP < ++totalP) {
				return false;
			}
		case 'S':
			if (maxS < ++totalS) {
				return false;
			}
		case 'F':
			if (maxF < ++totalF) {
				return false;
			}
		case 'B':
			if (maxB < ++totalB) {
				return false;
			}
		}
	}
	else {
		if (maxJ < ++totalJ) {
			return false;
		}
	}

	board[m][n] = &piece;
	return true;
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

bool Board::initBoard()
{	
	int x, y;
	bool joker;
	bool feof = false;
	Piece::PieceType pt;
	char line[10];
	//read file of player a
	ifstream player1File("player1.rps_board");
	while (!feof) {
		player1File.getline(line, 10);
		if (player1File.eof()) {
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
		Piece soldier = {pt, joker, x, y, 1};
		AddPiece(soldier);
	}
	return false;
}

Board::~Board()
{
	for (int i = 0; i < m; i++)
		delete []board[i];
	delete []board;
}
