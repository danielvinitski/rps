#include<iostream>
#include<fstream>
#include "Board.h"
#include "Player.h"
#include "main.h"
using namespace std;

int main() {
	Player* winner = nullptr;
	Board board = Board(10, 10);
	if (!board.initBoard())
		cout << board.getMessage() << endl;
	//board.printBoard("show 1", 50);

	board.printBoard("show 1", 50);
	while (board.scanBoard()) {

	}
	winner = board.getWinner();
	if (winner) {
		cout << "winner is player " << winner->getPlayerNumber() << endl;
	}
	else {
		cout << board.getMessage() << endl;
	}
}


