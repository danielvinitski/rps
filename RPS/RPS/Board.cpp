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
	return true;
}

bool Board::initBoard()
{	
	char line[10];
	//read file of player a
	ifstream player1File("player1.rps_board");
	player1File.getline(line, 10);



	return false;
}

Board::~Board()
{
	for (int i = 0; i < m; i++)
		delete []board[i];
	delete []board;
}
