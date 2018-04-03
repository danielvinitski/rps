#pragma once
class Player
{
	int playerNum;
	int totalR = 0, totalP = 0, totalS = 0, totalF = 0, totalJ = 0, totalB = 0;

public:
	Player(int num);
	~Player();
	int getPlayerNumber();

	int getTotalR();
	void setTotalR(int n);
	int getTotalP();
	void setTotalP(int n);
	int getTotalS();
	void setTotalS(int n);
	int getTotalF();
	void setTotalF(int n);
	int getTotalJ();
	void setTotalJ(int n);
	int getTotalB();
	void setTotalB(int n);
};

