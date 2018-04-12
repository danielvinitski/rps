#include<iostream>
#include<fstream>
#include "Game.h"
#include "move.h"
#include "Board.h"
using namespace std;

Game::Game()
{
}


Game::~Game()
{
}


Move* Game::getMove(int _plyer, string line) {
	char inputLine[11];
	for (char&c : inputLine) {
		c = 'e';
	}
	int i = 0;
	int player = _plyer;
	char curX, curY, tarX, tarY, jX, jY, newType;
	for (char& c : line) {
		if (c != ' ') {
			if (i < 11) {
				inputLine[i] = c;
				i += 1;
			}
			else {
				cout << "player " << _plyer << "to many chars in one line" << endl;
				return nullptr;
			}
		}
	}
	if (inputLine[0] >= '0' && inputLine[0] <= '9')
		curX = inputLine[0];
	else {
		cout << "player " << _plyer << "1 input in line wrong" << endl;
		return nullptr;
	}
	if (inputLine[1] >= '0' && inputLine[1] <= '9')
		curY = inputLine[1];
	else {
		cout << "player " << _plyer << "2 input in line wrong" << endl;
		return nullptr;
	}
	if (inputLine[2] >= '0' && inputLine[2] <= '9')
		tarX = inputLine[2];
	else {
		cout << "player " << _plyer << "3 input in line wrong" << endl;
		return nullptr;
	}
	if (inputLine[3] >= '0' && inputLine[3] <= '9')
		tarY = inputLine[3];
	else {
		cout << "player " << _plyer << "4 input in line wrong" << endl;
		return nullptr;
	}
	if (inputLine[4] == 'e' && inputLine[5] == 'e' && inputLine[6] == 'e' && inputLine[7] == 'e' && inputLine[8] == 'e' && inputLine[9] == 'e' && inputLine[10] == 'e')
		return new Move(player, curX, curY, tarX, tarY, false);
	else if (inputLine[4] == '[' && inputLine[5] == 'J' && inputLine[6] == ':' && inputLine[10] == ']') {
		if (inputLine[7] >= '0' && inputLine[7] <= '9') {
			jX = inputLine[7];
		}
		else {
			cout << "player " << _plyer << "8 input in line wrong" << endl;
			return nullptr;
		}
		if (inputLine[8] >= '0' && inputLine[8] <= '9') {
			jY = inputLine[8];
		}
		else {
			cout << "player " << _plyer << "8 input in line wrong" << endl;
			return nullptr;
		}
		if (inputLine[9] == 'R' || inputLine[9] == 'P' || inputLine[9] == 'S') {
			newType = inputLine[9];
		}
		else {
			cout << "player " << _plyer << "newType input wrong" << endl;
			return nullptr;
		}
		return new Move(player, curX, curY, tarX, tarY, true, jX, jY, newType);
	}
	else {
		cout << "player " << _plyer << "J input in line wrong" << endl;
		return nullptr;
	}
}

void Game::generateOutput() {
	Board board = *gameBoard;
	ofstream outFile("rps.output", ofstream::out);
	outFile << "Winner: " << board.getWinner() << endl;
	outFile << "Reason: " << board.getMessage() << endl << endl;
	board.printBoard(outFile);
}

void Game::start(int n, int m, int delay, string mode) {
	int winner;
	gameBoard = new Board(n, m);
	Board board = *gameBoard;
	if (board.initBoard()) {
		board.scanBoard();
		board.printBoard(mode, delay);
		string line1, line2;
		int fileLineCounter1 = 0, fileLineCounter2 = 0;
		bool finishMove1 = false;
		bool finishMove2 = false;
		ifstream player1MoveFile("player1.rps_moves");
		ifstream player2MoveFile("player2.rps_moves");
		Move* move1 = nullptr;
		Move* move2 = nullptr;
		while ((board.getWinner() == -1 || board.getWinner() == 0) && !(finishMove1 && finishMove2)) {
			if (!finishMove1) {
				fileLineCounter1 += 1;
				getline(player1MoveFile, line1);
				if (player1MoveFile.eof()) {
					finishMove1 = true;
				}
				if (line1.size() != 0) {
					move1 = getMove(0, line1);
				}
				if (move1 != nullptr || line1.size() != 0) {
					if (!board.MovePiece(move1)) break;
					board.printBoard(mode, delay);
					if (!board.scanBoard()) break;
				}
			}
			if (!finishMove2) {
				fileLineCounter2 += 1;
				getline(player2MoveFile, line2);
				if (player2MoveFile.eof()) {
					finishMove2 = true;
				}
				if (line2.size() != 0) {
					move2 = getMove(1, line2);
				}
				if (move2 != nullptr || line2.size() != 0) {
					if (!board.MovePiece(move2)) break;
					board.printBoard(mode, delay);
					if (!board.scanBoard()) break;
				}
			}
			if (move1 == nullptr && move2 == nullptr && line2.size() != 0 && line1.size() != 0) {
				board.setMessage("Bad Positioning input file for both players - player 1: line " + to_string(fileLineCounter1) + ", player 2: line " + to_string(fileLineCounter2));
				break;
			}
			else if (move1 == nullptr && line1.size()) {
				board.setWinner(2);
				board.setMessage("Bad Positioning input file for player 1 - line " + to_string(fileLineCounter1));
				break;
			}
			else if (move2 == nullptr && line2.size()) {
				board.setWinner(1);
				board.setMessage("Bad Positioning input file for player 2 - line " + to_string(fileLineCounter2));
				break;
			}
		}
		player1MoveFile.close();
		player2MoveFile.close();
	}
	winner = board.getWinner();
	string message = board.getMessage();
	if (winner == -1 || winner == 0) {
		if (board.getMessage().size() == 0) {
			board.setMessage("A tie - both Moves input files done without a winner");
			board.setWinner(0);
		}
	}
}