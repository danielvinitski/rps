#include<iostream>
#include<fstream>
#include "Board.h"
#include "main.h"
using namespace std;

int main() {
	Board board = Board(10,10);
	if (!board.initBoard())
		cout << "problem with the board init" << endl;
	board.printBoard("show-all", 50);
}


