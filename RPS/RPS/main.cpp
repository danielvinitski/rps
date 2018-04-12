#include<iostream>
#include<fstream>
#include "Board.h"
#include "Game.h"
#include "main.h"
using namespace std;


int main(int argc, char *argv[]) {
	const int delay = 100;
	const int N = 10;
	const int M = 10;
	const string mode = "show-all";

	Game game = Game();
	game.start(N, M, delay, mode);
	game.generateOutput();
}