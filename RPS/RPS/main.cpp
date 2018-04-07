#include<iostream>
#include<fstream>
#include "Board.h"
#include "Player.h"
#include "main.h"
using namespace std;

int main() {
	Player* winner = nullptr;
	Board board = Board(10,10);
	if (!board.initBoard())
		cout << "problem with the board init" << endl;
	//board.printBoard("show 1", 50);
	
	winner = board.scanBoard();
	board.printBoard("show 1", 50);
	while ((winner != nullptr)) {
		
	}
	cout << "winner is player " << winner->getPlayerNumber() << endl;
}


