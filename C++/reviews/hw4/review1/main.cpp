#define _CRT_RAND_S
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "graph.h"
using namespace std;

enum COLORS {
	WHITE, BLACK, NONE
};

int main(int argc, char* argv[]) {
	//cout << "started" << endl;
	srand(static_cast<int>(time(NULL)));
	//create 11 x 11 hex graph
	int size = 0;
	char buff[256];
	cout << "enter a board size greater than 2" << endl;
	while (size < 2) {
		cin.getline(buff, 256);
		size = atoi(buff);
		//cout << size << endl;
	}
	Graph G(size);
	G.printBoard();

	string line;
	int x, y;
	int turn = 0;
	string q;
	bool compMove = false;
	cout << "NEW GAME of HEX: player is WHITE, computer is BLACK." << endl;
	cout << "TYPE '-1' to exit the game" << endl;
	cout
			<< "to win, you must connect your pieces to make a path from LEFT to RIGHT."
			<< endl;
	//G.printBoard();
	G.p_win = false;
	G.c_win = false;

	while (G.p_win == false && G.c_win == false) {
		cout
				<< "enter an x,y coordinate (starting from 0,0 to " <<  size-1 << "," << size-1 << ") in this format: x,y" << endl;

		while (getline(cin, line)) {
			++turn;
			//cin >> q;
			//if (q == "q\n") return 0;
			istringstream tokenizer(line);
			string token;
			getline(tokenizer, token, ',');
			istringstream x_iss(token);
			x_iss >> x;
			if (!x_iss) {
				cout << "wrong input, please enter again in this format: x,y"
						<< endl;
				continue;
			}
			getline(tokenizer, token, ',');
			istringstream y_iss(token);
			y_iss >> y;
			if (!y_iss) {
				cout << "wrong input, please enter again in this format: x,y"
						<< endl;
				continue;
			}
			//quit game if player enters -1,-1
			if (x == -1 && y == -1)
				return 0;
			//check if out of range
			if (x >= sqrt(G.getOrder()) || y >= sqrt(G.getOrder())) {
				cout << "out of range, please enter again in this format: x,y"
						<< endl;
				continue;
			}
			if (G.playerMove(y, x) == false) {
				cout << "that space is occupied, please select another" << endl;
				continue;
			} else
				break;
		}
		cout << "your move is (" << x << ", " << y << ")" << endl;
		//check win for player
		G.checkWin(Graph::WHITE);
		//G.initializeVerts();
		//cout << G.vertices[0].color << endl;

		//do pie rule for first turn
		if (turn == 1) {
			//if computer choose to swap, go to next iteration of loop
			if (G.pie_rule(y, x) == true) {
				G.printBoard();
				continue;
			}
		}

		//select a legal move for computer
		//as long as player hasn't won yet
		if (G.p_win == false) {
			while (compMove == false) {
				compMove = G.computerMove(turn);
			}
			//check win for computer
			G.checkWin(Graph::BLACK);
		}
		G.printBoard();

		//reset computer move boolean
		compMove = false;
	}
	cout << "GAME OVER" << endl;
	if (G.p_win)
		cout << "PLAYER WINS" << endl;
	else if (G.c_win)
		cout << "COMPUTER WINS" << endl;
}
