#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <string>
#include<iostream>
#include<fstream>
#include <windows.h>

using namespace std;

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

bool Board::checkMaxTools(Player* player, const Piece::PieceType& p) {
	switch (p) {
	case Piece::PieceType::Rock:
		player->setTotalR(player->getTotalR() + 1);
		if (maxR < player->getTotalR()) {
			cout << "A PIECE type appears in file more than its number";
			return false;
		}
		break;
	case Piece::PieceType::Papper:
		player->setTotalP(player->getTotalP() + 1);
		if (maxP < player->getTotalP()) {
			cout << "A PIECE type appears in file more than its number";
			return false;
		}
		break;
	case Piece::PieceType::Scissors:
		player->setTotalS(player->getTotalS() + 1);
		if (maxS < player->getTotalS()) {
			cout << "A PIECE type appears in file more than its number";
			return false;
		}
		break;
	case Piece::PieceType::Flag:
		player->setTotalF(player->getTotalF() + 1);
		if (maxF < player->getTotalF()) {
			cout << "A PIECE type appears in file more than its number";
			return false;
		}
		break;
	case Piece::PieceType::Bomb:
		player->setTotalB(player->getTotalB() + 1);
		if (maxB < player->getTotalB()) {
			cout << "A PIECE type appears in file more than its number";
			return false;
		}
		break;
	}
	return true;
}

bool Board::AddPiece(Piece& piece) {
	Player* player = piece.getPlayer();
	bool maxNotReached = true;

	if (!piece.isJoker()) {
		maxNotReached = checkMaxTools(player, piece.getType());
		if (!maxNotReached) return false;
	}
	else {
		player->setTotalJ(player->getTotalJ() + 1);
		if (maxJ < player->getTotalJ()) {
			message = "A PIECE type appears in file more than its number";
			return false;
		}
	}

	if (board[piece.getY()-1][piece.getX()-1][player->getPlayerNumber() - 1]) {
		message = "Two or more PIECEs (of same player) are positioned on same location";
		return false;
	}
	board[piece.getY()-1][piece.getX()-1][player->getPlayerNumber() - 1] = &piece;
	return true;
}

void Board::setOppositeWinner(const int& player) {
	if (player == 1)
		winner = 2;
	else
		winner = 1;
}

Piece* Board::movePieceCheck(Move* move) {
	if ((move->getTargetX() > m && move->getTargetX() > 0) || (move->getTargetY() > n && move->getTargetY() < 0) || (move->getCurrentX() > m && move->getCurrentX() < 0) || (move->getCurrentY() > n && move->getCurrentY() < 0)) {
		cout << "X coordinate and/or Y coordinate of one or more PIECE is not in range";
		message = "X coordinate and/or Y coordinate of one or more PIECE is not in range";
		setOppositeWinner(move->getplayer());
		return nullptr;
	}
	if (board[move->getTargetY()][move->getTargetX()][move->getplayer() - 1]) {
		cout << "Two or more PIECEs (of same player) are positioned on same location";
		message = "Two or more PIECEs (of same player) are positioned on same location";
		setOppositeWinner(move->getplayer());
		return nullptr;
	}
	Piece *pieceToMove = board[move->getCurrentY()][move->getCurrentX()][move->getplayer() - 1];
	if (pieceToMove == nullptr) {
		cout << "moving not exsisting PIECE";
		message = "moving not exsisting PIECE";
		setOppositeWinner(move->getplayer());
		return nullptr;
	}
	if (pieceToMove->getType() == Piece::PieceType::Bomb || pieceToMove->getType() == Piece::PieceType::Flag) {
		cout << "illigal move (moving flag or bomb)";
		message = "moving not exsisting PIECE";
		setOppositeWinner(move->getplayer());
		return nullptr;
	}
	return pieceToMove;
}

bool Board::moveJockerPieceCheck(Move* move) {
	Piece *jockerToChange = board[move->getJokerY()][move->getJokerX()][move->getplayer() - 1];
	if (jockerToChange != nullptr && (*jockerToChange).isJoker()) {
		return true;
	}
	else {
		cout << "Joker position does not have a Joker owned by this player";
		setOppositeWinner(move->getplayer());
		return false;
	}
}

bool Board::MovePiece(Move* move) {
	Piece *jockerToChange;
	Piece *pieceToMove = movePieceCheck(move);
	if (pieceToMove != nullptr) {
		board[move->getCurrentY()][move->getCurrentX()][move->getplayer() - 1] = nullptr;
		board[move->getTargetY()][move->getTargetX()][move->getplayer() - 1] = pieceToMove;
		if (move->getJoker()) {
			if (moveJockerPieceCheck(move))
				(board[move->getJokerY()][move->getJokerX()][move->getplayer() - 1])->setType(getPieceTypeFromChar(move->getNewPieceType()));
			else return false;
		}
		return true;
	}
	return false;
}



bool Board::loadPlayer(ifstream& player, int playerNum, int& lineNum)
{	
	int x, y;
	bool joker, feof = false;
	Piece::PieceType pt;
	Player* playerObj = new Player(playerNum);
	char j, p;
	while (!player.eof()) {
		player >> j;
		if (player.eof()) break;
		player >> x >> y;
		if (j == 'J') {
			joker = true;
			player >> p;
		}
		else {
			joker = false;
			p = j;
		}
		lineNum += 1;
		if ((p == 'R' || p == 'S' || p == 'P' || p == 'B' || p == 'F') && (x <= n && x > 0) && (y <= n && y > 0)) { //check the first letter of the input
			pt = getPieceTypeFromChar(p);
			Piece *soldier = new Piece(pt, joker, x, y, playerObj, false);
			if (!AddPiece(*soldier)) return false;
		}
		else {
			cout << "Bad format in line " << to_string(lineNum) << " for player "<< playerNum<< endl;
			message = "Bad format in player " + to_string(playerNum) + " init file";
			return false;
		}
	}
	if (playerObj->getTotalF() != maxF) {
		cout << "Missing Flags - Flags are not positioned according to their number" << endl;
		return false;
	}
	return true;
}

bool Board::checkInitBoard(const bool& initfile1, const int& lineNumber1, const bool& initfile2, const int& lineNumber2) {
	if (!(initfile1 || initfile2)) {
		winner = 0;
		cout <<"Bad Positioning input file for both players - player 1: line " + to_string(lineNumber1) + ", player 2: line " + to_string(lineNumber2);
		message = "Bad Positioning input file for both players - player 1: line " + to_string(lineNumber1) + ", player 2: line " + to_string(lineNumber2);
		return false;
	}
	if (!initfile1) {
		winner = 2;
		cout << "Bad Positioning input file for player 1 - line " + to_string(lineNumber1);
		message = "Bad Positioning input file for player 1 - line " + to_string(lineNumber1);
		return false;
	}
	if (!initfile2) {
		winner = 1;
		cout << "Bad Positioning input file for player 2 - line " + to_string(lineNumber2);
		message = "Bad Positioning input file for player 2 - line " + to_string(lineNumber2);
		return false;
	}
	return true;
}

bool Board::initBoard()
{
	int lineNumber1=0;
	int lineNumber2=0;
	bool initfile1, initfile2;
	//read file of player a
	ifstream player1File("player1.rps_board");

	//read file of player b
	ifstream player2File("player2.rps_board");

	initfile1 = loadPlayer(player1File, 1, lineNumber1);
	player1File.close();
	initfile2 = loadPlayer(player2File, 2, lineNumber2);
	player2File.close();
	return checkInitBoard(initfile1, lineNumber1, initfile2, lineNumber2);
}

void Board::goToXY(const int x, const int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Board::printBoard(string mode, int delay)
{
	//printLine();
	if (mode.compare("-quiet") != 0) {
		goToXY(0, 10);
		int i, j;
		cout << "    ----------------------------------------" << endl << "    | ";
		for (i = 1; i < 11; i++) {
			if(i!=10)
				cout << i <<  " | ";
			else
				cout << i << "|";
		}
		cout << endl;
		for (i = 0; i < 10; i++) {
			cout << "--------------------------------------------" << endl;
			if(i != 9)
				cout << "| " << i+1 << " | ";
			else
				cout << "|" << i + 1 << " | ";
			for (j = 0; j < 10; j++) {
				printSquare(i, j, mode);
			}
			cout << endl;
		}
			cout << "--------------------------------------------" << endl;
			Sleep(delay);
	}
}

void Board::printSquare(int i, int j, string mode) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char pieceType = ' ';
	int k = 15;

	if (board[i][j][0]) {
		k = 10;
		if ((mode.compare("-show 2") == 0 || mode.compare("-show-only-known-info") == 0) && !((*(board[i][j][0])).isRevealed()))
			pieceType = 'H';
		else {
			pieceType = getPieceStringFromEnum((*(board[i][j][0])).getType());
			if ((*(board[i][j][0])).isJoker())
				k += 8;
		}
	}
	if (board[i][j][1]) {
		k = 12;
		if ((mode.compare("-show 1") == 0 || mode.compare("-show-only-known-info") == 0) && !(*(board[i][j][1])).isRevealed())
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

void Board::printBoard(ofstream& outfile)
{	
	//printLine();
	int i, j;
	for (i = 0; i < 10; i++) {
		outfile << "--------------------------------------------------" << endl;
		outfile << "| ";
		for (j = 0; j < 10; j++) {
			printSquare(i, j, outfile);
		}
		outfile << endl;
	}
		outfile << "--------------------------------------------------" << endl;
}

void Board::printSquare(int i, int j,ofstream& outfile) {
	char pieceType = ' ';
	char player = ' ';
	if (board[i][j][0]) {
		pieceType = getPieceStringFromEnum((*(board[i][j][0])).getType());
		player = '1';
	}
	if (board[i][j][1]) {
		pieceType = getPieceStringFromEnum((*(board[i][j][1])).getType());
		player = '2';
	}
	outfile << pieceType << player;
	outfile << " | ";
}


Board::~Board()
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 2; k++)
				delete[]board[i][j][k];
			delete[]board[i][j];
		}
		delete[]board[i];
	}
	delete[]board;
}

bool Board::scanBoard() { //return true if game isn't over
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			if (board[i][j][0] != nullptr && board[i][j][1] != nullptr) {
				Player* player1 = board[i][j][0]->getPlayer();
				Player* player2 = board[i][j][1]->getPlayer();
				combat(i, j);
				winner = checkForWinner(player1, player2);
			}
	}
	return winner == -1 && message.size() == 0;
}

void Board::combat(int y, int x) {
	Piece* piece1 = board[y][x][0];
	Piece* piece2 = board[y][x][1];
	Player* player1 = piece1->getPlayer();
	Player* player2 = piece2->getPlayer();
	Piece::PieceType t1 = piece1->getType();
	Piece::PieceType t2 = piece2->getType();

	//reveal both
	piece1->setRevealed(true);
	piece2->setRevealed(true);

	//combat
	if ((t1 == Piece::PieceType::Bomb || t2 == Piece::PieceType::Bomb) || t1 == t2) {
		removePiece(y, x, piece1);
		removePiece(y, x, piece2);
		return;
	}

	if (t1 == Piece::PieceType::Flag && t2 != Piece::PieceType::Flag) {
		removePiece(y, x, piece1);
		return;
	}
	if (t2 == Piece::PieceType::Flag && t1 != Piece::PieceType::Flag) {
		removePiece(y, x, piece2);
		return;
	}

	if ((t1 == Piece::PieceType::Rock && t2 == Piece::PieceType::Scissors) ||
		(t1 == Piece::PieceType::Scissors && t2 == Piece::PieceType::Papper) ||
		(t1 == Piece::PieceType::Papper && t2 == Piece::PieceType::Rock)) {
		removePiece(y, x, piece2);
		return;
	}
	if ((t2 == Piece::PieceType::Rock && t1 == Piece::PieceType::Scissors) ||
		(t2 == Piece::PieceType::Scissors && t1 == Piece::PieceType::Papper) ||
		(t2 == Piece::PieceType::Papper && t1 == Piece::PieceType::Rock)) {
		removePiece(y, x, piece1);
		return;
	}
}

void Board::removePiece(int y, int x, Piece* piece) {
	Player* player = piece->getPlayer();
	int playerNum = player->getPlayerNumber() - 1;

	//remove piece
	board[y][x][playerNum] = nullptr;

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

int Board::checkForWinner(Player* player1, Player* player2) {
	bool player1Won = false, player2Won = false;

	//flags are killed
	if (player1->getTotalF() == 0) {
		message = "All flags of the opponent are captured";
		player2Won = true; 
	}
	if (player2->getTotalF() == 0) { 
		message = "All flags of the opponent are captured";
		player1Won = true;
	}

	//all other soldiers are killed
	if ((player1->getTotalR() +
		player1->getTotalP() + player1->getTotalS() + player1->getTotalJ()) == 0) {
		message = "All moving PIECEs of the opponent are eaten";
		player2Won = true;
	}
	if ((player2->getTotalR() +
		player2->getTotalP() + player2->getTotalS() + player2->getTotalJ()) == 0) {
		message = "All moving PIECEs of the opponent are eaten";
		player1Won = true;
	}

	//make sure not a tie
	if (player1Won && !player2Won) return 1;
	else if (!player1Won && player2Won) return 2;
	else if (player1Won && player2Won) {
		if(player1->getTotalF() == 0 && player2->getTotalF() == 0)
			message = "All flags of both the opponents are captured";
		else
			message = "All moving PIECEs of both the opponents are eaten";
		return 0;
	}
	else return -1;
}

string Board::getMessage() {
	return message;
}

int Board::getWinner() {
	return winner;
}