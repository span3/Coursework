#ifndef HEX_H
#define HEX_H
#include <vector>

using namespace std;

class Hex{
	public:
		char **board;
		int compX;
		int compY;
		int playX;
		int playY;
		bool playerTurn;
		Hex(int x=11):size(x) { }
		void create_board();
		void pie_check (char response, int prevX, int prevY);
		void update_board(int move_x,int move_y);
		void print_board();
		vector<int> check_neighbors(int position);
		bool check_win();
		void computer_move();
		void player_move();
	private:
		int size;
		int disp_size;
		char playerColor;
};

#endif
