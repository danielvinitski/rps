#include "Player.h"



Player::Player(int num)
{
	playerNum = num;
}


Player::~Player()
{
}

int Player::getPlayerNumber() {
	return playerNum;
}

int Player::getTotalR() {
	return totalR;
}
void Player::setTotalR(int n) {
	totalR = n;
}
int Player::getTotalP() {
	return totalP;
}
void Player::setTotalP(int n) {
	totalP = n;
}
int Player::getTotalS() {
	return totalS;
}
void Player::setTotalS(int n) {
	totalS = n;
}
int Player::getTotalF() {
	return totalF;
}
void Player::setTotalF(int n) {
	totalF = n;
}
int Player::getTotalJ() {
	return totalJ;
}
void Player::setTotalJ(int n) {
	totalJ = n;
}
int Player::getTotalB() {
	return totalB;
}
void Player::setTotalB(int n) {
	totalB = n;
}