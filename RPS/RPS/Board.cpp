#include "Board.h"



Board::Board(int m, int n)
{
	m = m;
	n = n;
	board = new char *[m];
	for (int i = 0; i < m; i++)
		board[i] = new char[n];
}


Board::~Board()
{
	for (int i = 0; i < m; i++)
		delete []board[i];
	delete []board;
}
