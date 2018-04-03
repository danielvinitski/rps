#pragma once
class Piece
{
public:
	enum PieceType { Rock = 'R', Papper = 'P', Scissors = 'S', Bomb = 'B', Flag='F' };
	Piece(PieceType type, bool isJoker, int x, int y, int player);
	int getX();
	int getY();
	int getPlayer();
	bool isJoker();
	PieceType getType();
	~Piece();

private:
	PieceType type;
	int x, y, player;
	bool joker;
};

