#include<iostream>
#include<fstream>
#include "Board.h"
#include "Player.h"
#include "main.h"
#include "move.h"
using namespace std;

int getFileLenght(string fileName) {
	ifstream file(fileName);
	
	int fileLen = 0;
	char line[20];
	bool feof = false;
	while (!feof) {
		file.getline(line, 20);
		if (file.eof()) {
			feof = true;
		}
		if (line[0] == 'J' || (line[0] <= '9' && line[0] >= 0)) {
			fileLen += 1;
		}
		else {
			file.close();
			return -1;
		}
	}
	file.close();
	return fileLen;
}

Move* getMove(int plyer, char* line) {

	if ((line[0] <= '9' && line[0] >= '0') && (line[2] <= '9' && line[2] >= '0') && (line[4] <= '9' && line[4] >= '0') && (line[6] <= '9' && line[6] >= '0') && (line[9] == 'J' && (line[12] <= '9' && line[3] >= '12') && (line[14] <= '9' && line[14] >= '0') && (line[16] == 'R' || line[16] == 'P' || line[16] == 'S'))) {
		Move* move = new Move(plyer, line[0], line[2], line[4], line[6], true, line[12], line[14], line[16]);
		return move;
	}
	else if ((line[0] <= '9' && line[0] >= '0') && (line[2] <= '9' && line[2] >= '0') && (line[4] <= '9' && line[4] >= '0') && (line[6] <= '9' && line[6] >= '0')) {
		Move* move = new Move(plyer, line[0], line[2], line[4], line[6], false);
	}
	else {
		return nullptr;
	}
}

Move** initMoves(int file1Len, int file2Len) {
	char line[20];
	bool feof1 = false, feof2 = false;
	if (file1Len == -1 || file2Len == -1) {
		return nullptr;//problem with the files
	}
	Move** moveList = new Move*[file1Len + file2Len];
	ifstream player1MoveFile("player1.rps_moves");
	ifstream player2MoveFile("player2.rps_moves");
	int i = 0, j = 0, k = 0;
	while (i != file1Len && j != file2Len) {
		if (i != file1Len) {
			player1MoveFile.getline(line, 10);
			moveList[k] = getMove(0, line);
			if (moveList[k] == nullptr)
				return nullptr;
			k += 1;
			i += 1;

		}
		if (j != file2Len) {
			moveList[k] = getMove(1, line);
			if (moveList[k] == nullptr)
				return nullptr;
			k += 1;
			j += 1;
		}
	}
	player1MoveFile.close();
	player2MoveFile.close();
	return moveList;
}

int main() {
	Player* winner = nullptr;
	Board board = Board(10, 10);
	if (!board.initBoard())
		cout << board.getMessage() << endl;
	//board.printBoard("show 1", 50);
	
	winner = board.scanBoard();
	board.printBoard("show-all", 50);
	int file1Len = getFileLenght("player1.rps_moves");
	int file2Len = getFileLenght("player2.rps_moves");
	Move** moveList = initMoves(file1Len, file2Len);
	if (moveList ==nullptr)
		cout << "problem with the moveList init" << endl;
	bool eol = false;
	int playedMoves = 0;
	while (winner != nullptr || (playedMoves<file1Len + file2Len)) {
		board.MovePiece(moveList[playedMoves]);
		winner = board.scanBoard();
		board.printBoard("show-all", 50);
		playedMoves += 1;
	}
	winner = board.getWinner();
	if (winner) {
		cout << "winner is player " << winner->getPlayerNumber() << endl;
	}
	else {
		cout << board.getMessage() << endl;
	}
}


