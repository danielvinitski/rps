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

bool Game::checkMove(const int& curX, const int& curY, const int& tarX, const int& tarY, const bool& joker, const int& jX, const int& jY, const char& newType) {
	if (!((curX < 11 && curX>0) && (curY < 11 && curY>0) && (tarX < 11 && tarX>0) && (tarY < 11 && tarY>0)))
		return false;
	if (joker)
		return ((jX < 11 && jX>0) && (jY < 11 && jY>0) && (newType == 'R' || newType == 'S' || newType == 'P'));
	return true;
}

Move* Game::setMove(const string* moveList, const int& player) {
	int jX, jY, curX, curY, tarX, tarY;
	char newType;
	if (moveList[0].compare("")!=0 && moveList[1].compare("") != 0 && moveList[2].compare("") != 0 && moveList[3].compare("") != 0) {
		curX = stoi(moveList[0]);
		curY = stoi(moveList[1]);
		tarX = stoi(moveList[2]);
		tarY = stoi(moveList[3]);
	}
	else return nullptr;
	bool joker = false;
	if (moveList[4].compare("J:")==0) {
		joker = true;
	}
	if (joker) {
		if (moveList[5].compare("") != 0 && moveList[6].compare("") != 0 && moveList[7].compare("")) {
			jX = stoi(moveList[5]);
			jY = stoi(moveList[6]);
			newType = moveList[7][0];
		}
		else return nullptr;
	}
	if (checkMove(curX,curY,tarX,tarY,joker,jX,jY,newType)) {
		if(joker)
			return new Move(player, curX, curY, tarX, tarY, true, jX, jY, newType);
		else
			return new Move(player, curX, curY, tarX, tarY, false);
	}
	else return nullptr;
}

Move* Game::getMove(const int _player, string line) {
	int i = 0;
	string inputLine[11];
	bool empty = true;
	for (char& c : line) {
		if (c != ' ') {
			if (i < 11) {
				inputLine[i] += c;
				empty = false;
			}
			else {
				cout << "player " << _player << "to many chars in one line" << endl;
				return nullptr;
			}
		}
		else if(!empty){
			i += 1;
			empty = true;
		}
	}
	Move* move = setMove(inputLine, _player);
	return move;
}

void Game::generateOutput(Board& board) {
	ofstream outFile("rps.output", ofstream::out);
	outFile << "Winner: " << board.getWinner() << endl;
	outFile << "Reason: " << board.getMessage() << endl << endl;
	board.printBoard(outFile);
}

bool Game::playMove(const int& player, int& fileLineCounter, ifstream& playerMoveFile,Board& board,const int& delay, const string& mode) {
	string line;
	Move* move = nullptr;
	bool finishMove = false;
	fileLineCounter += 1;
	getline(playerMoveFile, line);
	if (playerMoveFile.eof()) finishMove = true;
	if (line.size() != 0) move = getMove(player, line);
	if (move != nullptr || line.size() != 0) {
		if (!board.MovePiece(move)) { 
			board.setMessage("Bad Moves input file for player " + to_string(player) + " - line " + to_string(fileLineCounter));
			return false;
		}
		if (!board.scanBoard()) {
			board.printBoard(mode, delay);
			return false; 
		}
		else board.printBoard(mode, delay);
	}
	else if (move == nullptr && line.size()!=0) {
		board.setWinner(1);
		board.setMessage("Bad Positioning input file for player 2 - line " + to_string(fileLineCounter));
		return false;
	}
	delete move;
	return finishMove;
}

void Game::playGame(Board& board, const int& delay, const string& mode) {
	int fileLineCounter1 = 0, fileLineCounter2 = 0;
	bool finishMove1 = false, finishMove2 = false;
	ifstream player1MoveFile("player1.rps_moves");
	ifstream player2MoveFile("player2.rps_moves");
	while (!(finishMove1 && finishMove2)) {
		if (!finishMove1) {
			finishMove1 = playMove(1, fileLineCounter1, player1MoveFile, board, delay, mode);
			if ((board.getWinner() != -1 && board.getWinner() != 0)) break;
		}
		if (!finishMove2) {
			finishMove2 = playMove(2, fileLineCounter2, player2MoveFile, board, delay, mode);
			if ((board.getWinner() != -1 && board.getWinner() != 0)) break;
		}
	}
	player1MoveFile.close();
	player2MoveFile.close();
}

void Game::start(int n, int m, int delay, string mode) {
	int winner;
	gameBoard = new Board(n, m);
	Board board = *gameBoard;
	if (board.initBoard()) {// init all the positening 
		board.scanBoard();
		board.printBoard(mode, delay);
		if(board.getWinner() ==-1)
			playGame(board, delay, mode);
		winner = board.getWinner();
		if (winner == -1 || winner == 0) {
			if (board.getMessage().size() == 0) {
				board.setMessage("A tie - both Moves input files done without a winner");
				board.setWinner(0);
			}
		}
	}
	cout << endl <<"Game Over!";
	generateOutput(board);
	delete gameBoard;
}