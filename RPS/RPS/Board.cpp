#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <string>
#include<iostream>
#include<fstream>
#include <windows.h>

using namespace std;

const string red("\033[0;31m");
const string green("\033[1;32m");
const string reset("\033[0m");

Board::Board(int _m, int _n)
{
	m = _m;
	n = _n;
	board = new Piece ***[m];
	for (int i = 0; i < m; i++) {
		board[i] = new Piece**[n];
		for (int j = 0; j < n; j++) {
			board[i][j] = new Piece*[2];
			for (int k = 0; k < 2; k++) {
				board[i][j][k] = nullptr;
			}
		}
	}
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

char getPieceStringFromEnum(Piece::PieceType pieceType) {
	switch (pieceType) {
	case Piece::PieceType::Rock: return 'R';
	case Piece::PieceType::Papper: return 'P';
	case Piece::PieceType::Scissors: return 'S';
	case Piece::PieceType::Flag: return 'F';
	case Piece::PieceType::Bomb: return 'B';
	}
}

bool Board::AddPiece(Piece& piece) {
	Player* player = piece.getPlayer();

	if (piece.getX() > m - 1 || piece.getY() > n - 1) {
		message = "X coordinate and/or Y coordinate of one or more PIECE is not in range";
		return false;
	}

	if (!piece.isJoker()) {
		switch (piece.getType()) {
		case Piece::PieceType::Rock:
			player->setTotalR(player->getTotalR() + 1);
			if (maxR < player->getTotalR()) {
				message = "A PIECE type appears in file more than its number";
				return false;
			}
			break;
		case Piece::PieceType::Papper:
			player->setTotalP(player->getTotalP() + 1);
			if (maxP < player->getTotalP()) {
				message = "A PIECE type appears in file more than its number";
				return false;
			}
			break;
		case Piece::PieceType::Scissors:
			player->setTotalS(player->getTotalS() + 1);
			if (maxS < player->getTotalS()) {
				message = "A PIECE type appears in file more than its number";
				return false;
			}
			break;
		case Piece::PieceType::Flag:
			player->setTotalF(player->getTotalF() + 1);
			if (maxF < player->getTotalF()) {
				message = "A PIECE type appears in file more than its number";
				return false;
			}
			break;
		case Piece::PieceType::Bomb:
			player->setTotalB(player->getTotalB() + 1);
			if (maxB < player->getTotalB()) {
				message = "A PIECE type appears in file more than its number";
				return false;
			}
			break;
		}
	}
	else {
		player->setTotalJ(player->getTotalJ() + 1);
		if (maxJ < player->getTotalJ()) {
			message = "A PIECE type appears in file more than its number";
			return false;
		}
	}

	if (board[piece.getX()][piece.getY()][player->getPlayerNumber() - 1]) {
		message = "Two or more PIECEs (of same player) are positioned on same location";
		return false;
	}
	board[piece.getX()][piece.getY()][player->getPlayerNumber() - 1] = &piece;

	return true;
}

bool Board::MovePiece(int fromX, int fromY, int toX, int toY, int player) {
	if (toX > m - 1 || toY > n - 1 || fromX > m - 1 || fromY > n - 1) {
		message = "X coordinate and/or Y coordinate of one or more PIECE is not in range";
		return false;
	}
	if (board[toX][toY][player - 1]) {
		message = "Two or more PIECEs (of same player) are positioned on same location";
		return false;
	}

	Piece *pieceToMove = board[fromX][fromY][player - 1];
	board[fromX][fromY][player - 1] = nullptr;
	board[toX][toY][player - 1] = pieceToMove;
}
bool Board::MovePiece(int fromX, int fromY, int toX, int toY, int player, Piece::PieceType changeJokerType) {
	if (MovePiece(fromX, fromY, toX, toY, player)) {

		Piece *pieceToMove = board[fromX][fromY][player - 1];
		if ((*pieceToMove).isJoker()) {
			(*pieceToMove).setType(changeJokerType);
		}
		else {
			message = "Joker position doesn’t have a Joker owned by this player";
		}
	}
	else return false;
}
void Board::MovePiece(Move* move) {
	Piece *pieceToMove = board[move->getCurrentX()][move->getCurrentY()][move->getplayer()];
	board[move->getCurrentX()][move->getCurrentY()][move->getplayer()] = nullptr;
	board[move->getTargetX()][move->getTargetY()][move->getplayer()] = pieceToMove;
	if (move->getJoker()) {
		(board[move->getJokerX()][move->getJokerY()][move->getplayer()])->setType(getPieceTypeFromChar(move->getNewPieceType()));
	}
}


bool Board::loadPlayer(ifstream& player, int playerNum)
{
	int x, y;
	bool joker;
	bool feof = false;
	Piece::PieceType pt;
	Player* playerObj = new Player(playerNum);
	char line[10];
	while (!feof) {
		player.getline(line, 10);
		if (player.eof()) {
			feof = true;
		}
		if (!(line[0] == 'R' || line[0] == 'S' || line[0] == 'P' || line[0] == 'J' || line[0] == 'B' || line[0] == 'F')) { //check the first letter of the input
			message = "Bad format";
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
		Piece *soldier = new Piece(pt, joker, x, y, playerObj, false);
		if (!AddPiece(*soldier))
			return false;
	}
	player.close();

	if (playerObj->getTotalF() != maxF) {
		message = "Missing Flags - Flags are not positioned according to their number";
		return false;
	}

	return true;
}


bool Board::initBoard()
{
	//read file of player a
	ifstream player1File("player1.rps_board");
	//read file of player b
	ifstream player2File("player2.rps_board");
	return loadPlayer(player1File, 1) && loadPlayer(player2File, 2);
}

void printLine() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int k;
	for (k = 1; k < 255; k++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(hConsole, k);
		cout << k << " I want to be nice today!" << endl;
	}
}

bool Board::printBoard(string mode, int delay)
{
	//printLine();
	if (mode.compare("quiet") != 0) {
		int i, j;
		for (i = 0; i < 10; i++) {
			cout << "-----------------------------------------" << endl;
			cout << "| ";
			for (j = 0; j < 10; j++) {
				printSquare(i, j, mode);
			}
			cout << endl;
		}
		cout << "-----------------------------------------" << endl;
	}
	Sleep(delay);
	return true;
}

void Board::printSquare(int i, int j, string mode) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char pieceType = ' ';
	int k = 15;

	if (board[i][j][0]) {
		k = 10;
		if ((mode.compare("show 2") == 0 || mode.compare("show-only-known-info") == 0) && !((*(board[i][j][0])).isRevealed()))
			pieceType = 'H';
		else {
			pieceType = getPieceStringFromEnum((*(board[i][j][0])).getType());
			if ((*(board[i][j][0])).isJoker())
				k += 8;
		}
	}
	if (board[i][j][1]) {
		k = 12;
		if ((mode.compare("show 1") == 0 || mode.compare("show-only-known-info") == 0) && !(*(board[i][j][1])).isRevealed())
			pieceType = 'H';
		else {
			pieceType = getPieceStringFromEnum((*(board[i][j][1])).getType());
			if ((*(board[i][j][1])).isJoker())
				k += 8;
		}
	}
	SetConsoleTextAttribute(hConsole, k);
	cout << pieceType;
	SetConsoleTextAttribute(hConsole, 15);
	cout << " | ";
}

Board::~Board()
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			delete[]board[i][j];
		delete[]board[i];
	}
	delete[]board;
}

bool Board::scanBoard() { //return true if game isn't over
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (board[i][j][0] != nullptr && board[i][j][1] != nullptr) {
				Player* player1 = board[i][j][0]->getPlayer();
				Player* player2 = board[i][j][1]->getPlayer();
				combat(i, j);
				winner = checkForWinner(player1, player2);
			}

	return winner == nullptr && message.size() == 0;
}

void Board::combat(int x, int y) {
	Piece* piece1 = board[x][y][0];
	Piece* piece2 = board[x][y][1];
	Player* player1 = piece1->getPlayer();
	Player* player2 = piece2->getPlayer();
	Piece::PieceType t1 = piece1->getType();
	Piece::PieceType t2 = piece2->getType();

	//reveal both
	piece1->setRevealed(true);
	piece2->setRevealed(true);

	//combat
	if ((t1 == Piece::PieceType::Bomb || t2 == Piece::PieceType::Bomb) || t1 == t2) {
		removePiece(x, y, piece1);
		removePiece(x, y, piece2);
	}

	if (t1 == Piece::PieceType::Flag && t2 != Piece::PieceType::Flag) {
		removePiece(x, y, piece1);
	}
	if (t2 == Piece::PieceType::Flag && t1 != Piece::PieceType::Flag) {
		removePiece(x, y, piece2);
	}

	if ((t1 == Piece::PieceType::Rock && t2 == Piece::PieceType::Scissors) ||
		(t1 == Piece::PieceType::Scissors && t2 == Piece::PieceType::Papper) ||
		(t1 == Piece::PieceType::Papper && t2 == Piece::PieceType::Rock)) {
		removePiece(x, y, piece2);
	}
	if ((t2 == Piece::PieceType::Rock && t1 == Piece::PieceType::Scissors) ||
		(t2 == Piece::PieceType::Scissors && t1 == Piece::PieceType::Papper) ||
		(t2 == Piece::PieceType::Papper && t1 == Piece::PieceType::Rock)) {
		removePiece(x, y, piece1);
	}
}

void Board::removePiece(int x, int y, Piece* piece) {
	Player* player = piece->getPlayer();
	int playerNum = player->getPlayerNumber() - 1;

	//remove piece
	board[x][y][playerNum] = nullptr;

	//update total
	if (piece->isJoker()) {
		player->setTotalJ(player->getTotalJ() - 1);
	}
	else {

		switch (piece->getType()) {
		case Piece::PieceType::Bomb:
			player->setTotalB(player->getTotalB() - 1);
			break;
		case Piece::PieceType::Flag:
			player->setTotalF(player->getTotalF() - 1);
			break;
		case Piece::PieceType::Rock:
			player->setTotalR(player->getTotalR() - 1);
			break;
		case Piece::PieceType::Scissors:
			player->setTotalS(player->getTotalS() - 1);
			break;
		case Piece::PieceType::Papper:
			player->setTotalP(player->getTotalP() - 1);
			break;
		}
	}
}

Player* Board::checkForWinner(Player* player1, Player* player2) {
	bool player1Won = false, player2Won = false;

	//flags are killed
	if (player1->getTotalF() == 0) player2Won = true;
	if (player2->getTotalF() == 0)  player1Won = true;

	//all other soldiers are killed
	if ((player1->getTotalB() + player1->getTotalR() +
		player1->getTotalP() + player1->getTotalS() + player1->getTotalJ()) == 0) player2Won = true;
	if ((player2->getTotalB() + player2->getTotalR() +
		player2->getTotalP() + player2->getTotalS() + player2->getTotalJ()) == 0) player1Won = true;

	//make sure not a tie
	if (player1Won && !player2Won) return player1;
	else if (!player1Won && player2Won) return player2;
	else return nullptr;
}

string Board::getMessage() {
	return message;
}

Player* Board::getWinner() {
	return winner;
}