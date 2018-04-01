#include<iostream>
#include<fstream>
#include "Board.h"
#include "main.h"
using namespace std;

int main() {
	Board board = Board(10,10);
	return board.initBoard();
}


