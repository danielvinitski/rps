#pragma once
class Piece
{
public:
	enum PieceType { Rock = 'R', Papper = 'P', Scissors = 'S', Bomb = 'B', Joker = 'J', Flag='F' };
	Piece(PieceType type, bool isJoker, int x, int y, int player);
	~Piece();

private:
	PieceType type;
	int x, y, player;
	bool isJoker;
};

