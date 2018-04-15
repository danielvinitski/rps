#pragma once
#include<fstream>
using namespace std;

class Move
{	
	bool joker = false;
	int jokerX = -1, jokerY = -1, currentX = 0, currentY = 0, targetX = 0, targetY = 0;
	int player;
	char newPieceType='R';

public:
	Move(int player, int curX, int curY, int tarX, int tarY, bool j);
	Move(int player, int curX, int curY, int tarX, int tarY, bool j, int jX, int jY,char newType);
	char getNewPieceType() { return newPieceType; }
	int getCurrentX() {return currentX;}
	int getCurrentY() {return currentY;}
	int getTargetX() {return targetX;}
	int getTargetY() {return targetY;}
	int getJokerX() { return jokerX; }
	int getJokerY() { return jokerY; }
	int getplayer() { return player; }
//	void setCurrentX(char x) { currentX = x - '0'; }
//	void setCurrentY(char y) { currentY = y - '0'; }
//	void setTargetX(char x) { targetX = x - '0'; }
//	void setTargetY(char y) { targetY = y - '0'; }
//	void setJokerX(char x) { jokerX = x - '0'; }
//	void setJokerY(char y) { jokerY = y - '0'; }
//	void setJoker(bool isJoker) {joker = isJoker;}
//	void setNewPieceType(char _newPieceType) { newPieceType = _newPieceType; }
	bool getJoker() { return joker; }
	~Move();
};

