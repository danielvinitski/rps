/*
דניאל ויניצקי 203245162
אופיר סונסינו 305346710
*/

#include<iostream>
#include<fstream>
#include "Board.h"
#include "Game.h"
#include "main.h"
using namespace std;

bool checkShowPlayer(const string& player) {
	if (player.compare("1") == 0 || player.compare("2")==0)
		return true;
	else return false;
}

bool isInteger(const string & s){
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
	}

string initParams(const int& argc,char *argv[], string& mode, int& delay ) {
	for (int i = 1; i < argc; i++) {
		string strArgv(argv[i]);
		if (strArgv.compare("-delay") == 0)
			if(isInteger(argv[i + 1]))
				delay = atoi(argv[i + 1]);
			else return "error in input args, delay must be number";
		else if (strArgv.compare("-quiet") == 0)
			mode = strArgv;
		if (mode.compare("-quiet") != 0) {
			if (strArgv.compare("-show-only-known-info") == 0)
				mode = strArgv;
			if (strArgv.compare("-show") == 0)
				if(checkShowPlayer(argv[i + 1]))
					mode = strArgv + " " + argv[i + 1];
				else {
					return "player number is inccorect try to pass -show 1 or -show 2";
				}
		}
	}
	return "";
}

int main(int argc, char *argv[]) {
	int delay = 50;
	const int N = 10;
	const int M = 10;
	string mode = "show-all";
	string error = "";
	error = initParams(argc, argv, mode, delay);
	if (error.size() == 0) {
		Game game = Game();
		game.start(N, M, delay, mode);
	}
	else {
		cout << error << endl;
	}
}

/*
player1.rps_board:
R 1 1

J 3 2 R
R 1 2
P 1 3
P 1 4
P 1 5
P 1 6
P 1 7
B 1 8
B 1 9
S 1 10
J 2 1 R

F 4 3

player2.rps_board:
R 9 10
R 9 1
P 9 2
P 9 3
P 9 4
P 9 5
P 9 6
B 9 7
B 9 8
S 9 9
J 8 1 R
J 8 2 R
F 8 3

player1.rps_moves:
1 1 9 9
1 10 8 9
9 9 7 9
3 2 8 3

player2.rps_moves:
9 5 1 1
9 2 7 1
9 6 5 1 [J: 8 1 S]

rps.output:
Winner: 1
Reason: All flags of the opponent are captured

--------------------------------------------------
| P2 | R1 |    |    | P2 |    | P2 | R2 | R2 |    |
--------------------------------------------------
| R1 |    |    |    |    |    |    | R2 |    |    |
--------------------------------------------------
| P1 |    |    | F1 |    |    |    | R1 | P2 |    |
--------------------------------------------------
| P1 |    |    |    |    |    |    |    | P2 |    |
--------------------------------------------------
| P1 |    |    |    |    |    |    |    |    |    |
--------------------------------------------------
| P1 |    |    |    |    |    |    |    |    |    |
--------------------------------------------------
| P1 |    |    |    |    |    |    |    | B2 |    |
--------------------------------------------------
| B1 |    |    |    |    |    |    |    | B2 |    |
--------------------------------------------------
| B1 |    |    |    |    |    | R1 | S1 |    |    |
--------------------------------------------------
|    |    |    |    |    |    |    |    | R2 |    |
--------------------------------------------------

*/