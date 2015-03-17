#include <vector>
#include <set>
#include "hex.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>

using namespace std;


void Hex::create_board() {
//create board
	playerTurn = false;
	disp_size = size+2;
	board = new char* [size];
	for(int i=0; i < size; i++){
		board[i] = new char[size];
	}
//fill board with default values
	for(int i=0; i < size; i++){
		for(int j=0; j < size; j++){
			board[i][j] = '*';
		}
	}
}

void Hex::pie_check (char response,int prevX,int prevY){
//make sure valid character
	while(response!='Y' && response!='N' && response!='y' && response!='n') {
		cout << "Please enter a valid character. Y/y for Yes and N/n for No." << endl;
		cin >> response;
	}
//if yes change the previous move to White and change playerTurn to be false
	if(response=='y' ||response=='Y'){
		cout << "You have chosen to use the pie rule." << endl;
		cout << "You have taken the computer's first move and still need to play vertically down the board to win." << endl; 
		playerTurn = true;
		update_board(prevX,prevY);
		playX = prevX;
		playY = prevY;
		playerTurn = false;
		print_board();
	}
//if no tell the user that they chose not to use the Pie Rule and it is now their turn, playerTurn=true and printScreen }	
	else {
		cout << "You chose not to use the pie rule." << endl;
		print_board();
		playerTurn=true;
	}
}
		

void Hex::update_board(int move_x,int move_y){
	if(playerTurn==true){
		board[move_x][move_y] = 'W';
	}
	else board[move_x][move_y] = 'B';
}

void Hex::print_board() {
	cout << "  ";
	for (int k=0; k < size; k++) {
		cout << k << " ";
	}
	cout << endl;
	for(int i=0;i<size;i++){
	    	int count = 0;
			for(count;count<i;count++){
			  cout<<" ";
			  }
			  cout<<i<<" ";
		/*cout << i << "  ";
		while(count < i){
			cout << " ";
			count++;
		} */
		for(int j=0;j<size;j++){
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
 
vector<int> Hex::check_neighbors(int position) {
//calculate neighbors for each node
	int left = position - 1;
	int right = position + 1;
	int bot_left = position + size - 1;
	int bot_right = position + size;
	int top_right = position - size + 1;
	int top_left = position - size;

//check if node is on top row
	if (position < size) {
		top_right = -1;
		top_left = -1;
	}
//check if node is on bottom row
	else if (position >= size*size - size) {
		bot_left = -1;
		bot_right = -1;
	}
//check if node is on left column
	if (position%size == 0) {
		left = -1;
	}
//check if node is on right column
	else if ((position+1)%size == 0) {
		right = -1;
	}
//put neighbors of node in a vector and return the vector
	vector<int> v(6,-1);
	v[0] = left;
	v[1] = right;
	v[2] = bot_left;
	v[3] = bot_right;
	v[4] = top_right;
	v[5] = top_left;
	return v;
}

bool Hex::check_win() {
	set<int> visited;
	set<int> current;

//check's white player's move based on its neighbors
	if (!playerTurn) {
		for (int i = 0; i < size; i++) {
			int source;
			if (board[0][i] == 'W' && (visited.find(i) == visited.end())) {
				source = i;
				current.insert(source);
			} 
			while (!current.empty()) {
				int current_first = *current.begin();
				vector<int> neighbors = check_neighbors(current_first);
				for(int j = 0; j <= 5; j++) {
					if (neighbors[j] != -1) {
						int row = neighbors[j]/size;
						int col = neighbors[j]%size;
						if (board[row][col] == 'W' && visited.find(neighbors[j]) == visited.end() 
						&& current.find(neighbors[j]) == current.end()) {
							current.insert(neighbors[j]);
						}
					}
				}
				set<int>::iterator iter;
				for(iter=current.begin(); iter!=current.end();++iter){
					if (*iter >= size*size - size) {
						cout << "You win!" << endl;
						return true;
					}
				}
				current.erase(current_first);
				visited.insert(current_first);

			}
		}
	}


//check Black player's neighbors
	if (playerTurn) {
		for (int i = 0; i < size; i++) {
			int source;
			if (board[i][0] == 'B' && visited.find(i) == visited.end()) {
				source = i*size;
				current.insert(source);
			} 
			while (!current.empty()) {
				int current_first = *current.begin();
				vector<int> neighbors = check_neighbors(current_first);
				for(int j = 0; j <= 5; j++) {
					if (neighbors[j] != -1) {
						int row = neighbors[j]/size;
						int col = neighbors[j]%size;
						if (board[row][col] == 'B' && visited.find(neighbors[j]) == visited.end() 
						&& current.find(neighbors[j]) == current.end()) {
							current.insert(neighbors[j]);
						}
					}
					
				}
				set<int>::iterator iter;
				for(iter=current.begin(); iter!=current.end();++iter){
					if ((*iter+1)%size == 0) {
						cout << "The computer wins. Sorry!" << endl;
						return true;
					}
				}
				current.erase(current_first);
				visited.insert(current_first);
			}
		}
	}
	return false;
}


void Hex::computer_move() {
	bool any_moves=false;
	cout << endl;
	cout << "It is now the computer's turn." <<endl;
//get a random number for the move if the player hasn't moved
	int x=0;
	int y=0;
if(playX==-1&& playY==-1) {
	x=rand()%(size-1);
	y=rand()%(size-1);
//check if the move is a valid move
	while(board[x][y] == 'W' || board[x][y] == 'B') {
		x=rand()%(size-1);
		y=rand()%(size-1);
	}
	cout << "The computer decided to place its move on x:" << x << " y:" << y << endl;
	}
//place the computer move around the previous player move
else {
//make an array of the surrounding elements (the neighbors)
	int validmoves[8][2];
    char sides[3][3];
	for(int i=0;i<8;i++){
	 for(int j=0;j<2;j++){
	   validmoves[i][j]=-1;
	   }
	}
//fill the array with the appropriate characters
	int count =0;
	for(int i=0;i<3;i++){
	 for(int j=0;j<3;j++){
	   if(playX+i-1==size ||playY+j-1==size || playX+i-1==-1 ||playY+j-1==-1){
	   sides[i][j]='x';
	   }
	   else{
	   sides[i][j]=board[playX+i-1][playY+j-1];
	   }
//check available moves from the sides array
       if(sides[i][j]=='*') {
	   any_moves=true;
	     x=playX+i-1;
		 y=playY+j-1;
		 validmoves[count][0]=x;
		 validmoves[count][1]=y;
		 count++;
		 }
	 }
	}
//if there are any moves available choose a random one available
if(any_moves==true){
int randSpot=rand()%8; 
//if the random spot is not valid make a new random spot
 while(validmoves[randSpot][0]==-1) {
  randSpot=rand()%8;
   }
   x=validmoves[randSpot][0];
   y=validmoves[randSpot][1];
 }
//if all moves are taken then get a random move
else{
x=rand()%(size-1);
y=rand()%(size-1);
//check if the move is a valid move
	while(board[x][y] == 'W' || board[x][y] == 'B') {
		x=rand()%(size-1);
		y=rand()%(size-1);
	}	
}
}
	compX=x;
	compY=y;
//update the board
	update_board(x,y);
//change the playerTurn to be true
	playerTurn = true;
//print the board
	print_board();
}
 
void Hex::player_move() { 
//get two values from the player
	cout << endl;
	cout << "It is now your turn. Please enter two integers between 0 and "<<size-1<<" with the horizontal coordinate first and then the vertical coordinate (ex. 1 1):" << endl;
	cin >> playX;
	cin >> playY;
//make sure it is valid between 1 and size, and move not taken
	while(playX > size || playY > size || board[playX][playY]=='W' || board[playX][playY]=='B') {
		if(playX>size||playY>size) {
			cout << "This move does not fit with the board size. Please enter a new move from 0 to "<<size-1<<": " << endl;
		}
		if(board[playX][playY]=='W' || board[playX][playY]=='B') {
			cout << "This move has already been played. Please enter a new move:" <<endl;
		}
		cin >> playX;
		cin >> playY;
	}
//update the board
	update_board(playX,playY);
//change playerTurn to be false
	playerTurn=false;
//print the board;
	print_board();
}

int main() {
	srand(time(NULL));
	cout << "Welcome to the Game of Hex! You will be playing 'White' which needs to be played top to bottom." << endl;
	cout << "The computer will be playing 'Black' which will be playing right to left." << endl; 
	cout << "Please enter an integer for the input size for the board." <<endl;
	cout << "Enter size. Type '0' for default size:" << endl;
	int x = -1;
	cin >> x;
	Hex game;
	if(x==-1) {
		Hex my_game;
		game=my_game;
	}
	else if(x == 0){
		Hex my_game;
		game = my_game;
	}
	else {
		Hex my_game(x);	
		game=my_game;
	}
	game.create_board(); 
//computer moves first
	game.playX=-1;
	game.playY=-1;
	game.computer_move();
//ask the user if they want to take advantage of the pie rule
	cout << "The computer has made its move first. Would you like to take advantage of the pie rule? Enter Y/y for yes and N/n for no:";
	char pieEval;
	cin >> pieEval;
	game.pie_check(pieEval,game.compX,game.compY);
//when it is not a win if player turn is true player move else computer move
	bool check = false;
	//bool check=game.check_win();
	while(check!=true){
		if(game.playerTurn==true) 
			game.player_move();
		else 
			game.computer_move();
		check=game.check_win();
	}
}