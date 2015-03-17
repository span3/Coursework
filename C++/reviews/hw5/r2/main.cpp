// main.cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <ctime>

#include "node.h"

using namespace std;















//recursively checks each node to see if its
//connected to the end (and a player wins)
bool checkWinRecurse(int curr, int color, int size, node board[]){

      //cout << curr <<" ";
      //if this tile is already visited, or already has a move on it, false
     if(board[curr].getVisited() == true){ return false; }
     if(board[curr].getColor() != color){	return false;  }

      //success condition, if checking for user, test for bottom row
      //if checking for computer, test for rightmost row
     if(color == 1){
          if(curr >= size*(size-1)) return true;
     }else{ //color == 2
          if(curr % size == size-1) return true;
     }

     //current tile, don't revisit
     board[curr].setVisited(true);
     
	 
	 
     //if(possible) recurse on neighbor.  Will return if visited or not matching color
     //check left neighbor   
      if(curr % size > 0){
         if(checkWinRecurse(curr - 1, color, size, board)){
		      return true;
	      }else{ 
            board[curr - 1].setVisited(false); //reset visit flag (if path doesn't recurse on that tile)
         }
      }
      //check right neighbor
      if(curr % size < size-1){ 
         if(checkWinRecurse(curr + 1, color, size, board)) {
		      return true;
	      }else{ 
            board[curr + 1].setVisited(false); //reset visit flag (if path doesn't recurse on that tile)
         }
      }

     //check up neighbor
      if(curr > size){
         if(checkWinRecurse(curr - size, color, size, board)){
		      return true;
         }else{ 
            board[curr - size].setVisited(false); //reset visit flag (if path doesn't recurse on that tile)
         }
      }
      //check down neighbor
      if(curr < size*(size-1)){
         if(checkWinRecurse(curr + size, color, size, board)){
      		return true;
	      }else{ 
            board[curr + size].setVisited(false); //reset visit flag (if path doesn't recurse on that tile)
         }
      }
     
     //check up-right neighbor
      if(curr > size && curr % size < size-1){
         if(checkWinRecurse(curr - size + 1, color, size, board)) {
      		return true;
	      }else{ 
            board[curr - size + 1].setVisited(false); //reset visit flag (if path doesn't recurse on that tile)
         }
      }
      //check down-left neighbor
      if(curr < size*(size-1) && curr % size > 0){
         if(checkWinRecurse(curr + size -1, color, size, board)) {
	   	   return true;
	      }else{ 
            board[curr + size -1].setVisited(false); //reset visit flag (if path doesn't recurse on that tile)
         }
      }
     
      //if no neighbors are found to recurse on, return to previous tile	
      return false;
}



//Check for winning condition
bool checkForWin(node board[], int size, int color){
     bool gameover = false;
     if(color == 1){     
          //testing up to down win (player)
          for(int i = 0; i < size; i++){
               if(board[i].getColor() == 1) {
                    //cout << "before";
                    gameover = checkWinRecurse(i, color, size, board);
                    //cout << "after \n";
		         }
               if(gameover){
                  //cout << "returning true";
                  return true;
		         }
		       //clear visited
		       for(int i = 0; i < size; i++){ board[i].setVisited(false); }
          }
     }else { 
          //testing for left to right win  (computer)
          for(int i = 0; i < size*(size-1); i+=size){
               if(board[i].getColor() == 2) {
                    //cout << "beforec";
                    gameover = checkWinRecurse(i, color, size, board);
                    //cout << "afterc\n";
		         }
               if(gameover){
                  //cout << "returning truec";
                  return true;
               }
		       
		       //clear visited
		       for(int i = 0; i < size; i++){ board[i].setVisited(false); }
          }
     }
   //cout << "ending";
   //cout << endl;
   return false;
}


void printBoard(int boardSizeIn, int boardSize, node A[]){
   int lineCounter = 1;

   
   cout << " \n";
   //Collumn numbers
   cout << "    ";
   for(int nums = 0; nums < boardSizeIn; nums++){

      if(nums > 9){
         cout << " " << nums << " ";
      }else{
         cout << " " << nums << "  ";
      }
   }
   cout << "\n";

   cout << "    ";
   for(int nums = 0; nums < boardSizeIn; nums++){
      cout << " / \\";
   }

   //replace with top line of hexes   
   cout << "\n";

   
   for(int i = 0; i< boardSizeIn; i++){
      //printing out line numbers
      if(i<10){
         cout << " " << i << "  ";   
      }else{
         cout << " " << i << " ";
      }

      //printing out hex tiles
      cout << "|";
      for(int j = 0; j < boardSizeIn; j++){
         if(A[j + (boardSizeIn*i)].getColor() == 0){
            cout << " " << "-" << " |";
         }else if(A[j + (boardSizeIn*i)].getColor() == 1){
            cout << " " << "x" << " |";
         }else if(A[j + (boardSizeIn*i)].getColor() == 2){
            cout << " " << "c" << " |";
         }
      }
      cout << "\n";

      //draw hex lines
      //indents to make it hexy
      for(int cc = 0; cc < lineCounter; cc++){
         cout << "  ";
      }
      cout << "   \\ ";
      for(int hdraw = 0; hdraw < boardSizeIn; hdraw++){
            cout << "/ \\ ";
      }
      cout << "\n";
      
      //indents to make it hexy
      for(int ccc = 0; ccc < lineCounter; ccc++){
         cout << "  ";
      }
      lineCounter++;
   }

   cout << "\n";
   
}







double monteCarloTrial(node A[], int boardSize, int boardSizeIn, int numTrials, int x, int y){
   
   //copy board
   int cx, cy;
   int wins = 0;
   node *C = new node[boardSize];
   for(int ii = 0; ii < boardSize; ii++){
      C[ii] = A[ii];
   }
   //add new move to new board
   C[y*boardSizeIn + x].setColor(2);
   
   for(int jj = 0; jj< numTrials; jj++){

      while(checkForWin(C, boardSizeIn, 1) || checkForWin(C, boardSizeIn, 2)){
         //random user moves
         cx = rand() % (boardSizeIn - 1);
         cy = rand() % (boardSizeIn - 1);

         while(C[cy*boardSizeIn +cx].getColor() != 0){
         cx = rand() % (boardSizeIn - 1);
         cy = rand() % (boardSizeIn - 1);
         }
         C[cy*boardSizeIn + cx].setColor(1);
         //random player moves

         while(C[cy*boardSizeIn +cx].getColor() != 0){
         cx = rand() % (boardSizeIn - 1);
         cy = rand() % (boardSizeIn - 1);
         }
         C[cy*boardSizeIn + cx].setColor(2);
        // cout << "After \n";
      }
      wins++;
   }
   
   return (wins/numTrials);
   //once finish loop, return wins divided by Trials

}



node* monteCarlo(node A[], int boardSizeIn, int boardSize){

int bestX = -1;
int bestY = -1;
int bestMove = 10000;
int numTrials = 1000;
int numMoves = 100;
int tempX, tempY;
for(int i = 0; i < numMoves; i++){
      //find a random move, put into
      //tempx and tempy
      tempX = rand() % (boardSizeIn - 1);
      tempY = rand() % (boardSizeIn - 1);
      while(A[tempY*boardSizeIn +tempX].getColor() != 0){
            tempX = rand() % (boardSizeIn - 1);
            tempY = rand() % (boardSizeIn - 1);
      }
      //run montycarlotrail and get a ratio to use for best move.
      int montyReturn = monteCarloTrial(A, boardSize, boardSizeIn, numTrials, tempX, tempY);
      
      //if MonteCarloTrial returns number smaller than bestmove, put those x/y into bestX/bestY
      bestX = tempX;
      bestY = tempY;
      //determine best move based on return
      if(montyReturn < bestMove){
         bestMove = montyReturn;
         bestX = tempX;
         bestY = tempY;
      }
           // cout<< "carlo for loop";
   }
      cout << "computer moves: " << bestX<<", "<<bestY;
     
   A[bestY*boardSizeIn + bestX].setColor(2);
   return A;
}




//Ai function from previous lab
void computerMove(int x, int y, int cx, int cy, int boardSizeIn, int halfboard, bool turn1, node A[]){

         //Find computer move
         if(y < boardSizeIn/2){
            cx = x;
            cy = y+1;
            if(A[cy*boardSizeIn +cx].getColor() != 0){
               cx = x;
               cy = y-1;
               if(cy < 0){
                  cy = boardSizeIn-1;
                  cx = cx + 1;
               }
            }
            if(cy < 0){
               cy = rand() % (boardSizeIn - 1);
            }
            while(A[cy*boardSizeIn +cx].getColor() != 0){
               cy = cy + 1;
               if(cy >= boardSizeIn-1){
                  cy = 0;
                  cx = cx + 1;
               }
            }
         }else if(y >= boardSizeIn/2){
            cx = x;
            cy = y-1;
            if(A[cy*boardSizeIn +cx].getColor() != 0){
               cx = x;
               cy = y+1;
               if(cy > boardSizeIn-1){
                  cy = 0;
                  cx = cx + 1;
               }
            }
            if(cy > boardSizeIn){
               cy = rand() % (boardSizeIn - 1);
            }
            while(A[cy*boardSizeIn +cx].getColor() != 0){
               cy = cy + 1;
               if(cy > boardSizeIn-1){
                  cy = 0;
                  cx = cx + 1;
               }

            }

         }else{
            cx = rand() % (boardSizeIn - 1);
            cy = rand() % (boardSizeIn - 1);
         }
          

            
         //Check for Pie rule condition
         if(turn1 == true && x == halfboard && y == halfboard){
            cx = x;
            cy = y;
            cout << "Invoking Pie Rule\n";
         }   
         turn1 = false;
         
         cout << "Computer moves " << cx << " " << cy << endl;
         //Set Computer move and print
         A[cy*boardSizeIn + cx].setColor(2);

}

//---------------------------------------------------------------------------

int main(){
     
     srand(time(NULL));

     cout << "Program begins \n\n\n";
     int boardSizeIn = 0;
     bool turn1 = true;

   //int lineCounter2 = 0;
   cout << "How many tiles wide should the board be? \n";
   bool validSize = true;
   while(validSize){
      cin >> boardSizeIn;
      if(boardSizeIn < 2){
         cout << "Board size too small, Re-Enter board size:\n";
      }else{
         validSize = false;
      }   
   }
   cout << "Creating board of size " << boardSizeIn << "\n";
   
   int boardSize = 0;
   boardSize =  boardSizeIn;
   boardSize = boardSize * boardSize;
   cout << boardSize << " Hexes total " << endl;
  	node *A = new node[boardSize];

   //for pie rule
   double halfboard;
   halfboard = boardSizeIn;
   halfboard = (halfboard/2) -.5;
   for(int fill = 0; fill < boardSize; fill++){
      	A[fill].setVisited(false);
         A[fill].setColor(0);
   }
   
   int x = -1, y = -1;
   int cx = -1, cy = -1;
   printBoard(boardSizeIn, boardSize, A);

   cout << "Begin Game. \n\nGoal of User is to choose tiles that \nwill connect the top to the bottom.  Good Luck\n";
   bool invalidMove = true;
    while(!(checkForWin(A, boardSizeIn, 1) || checkForWin(A, boardSizeIn, 2))){

         //Get player move, check validity
        while(invalidMove){
            cout << "Enter your move (eg. 4 5)(don't enter non numbers): \n"; 
            cin >> x;
            cin >> y;
            if(A[y*boardSizeIn + x].getColor() > 0){
               cout << "Invalid move. Tile already taken \nRe-";
            }else if(x > boardSizeIn-1 || y > boardSizeIn-1 || x < 0 || y < 0){
               cout << "Move is beyond board limits.  \nRe-";
            }else{
               invalidMove = false;
            }
         }
         invalidMove = true; //resetting flag var

         //Set user move and print
        // cout<< "before user move set";
         A[y*boardSizeIn + x].setColor(1);
         //cout<< "before print user board";
         printBoard(boardSizeIn, boardSize, A);
         
        // cout<< "before montecarlo";

         monteCarlo(A, boardSizeIn,boardSize);
         //computerMove(x, y, cx, cy, boardSizeIn, halfboard, turn1, A);
         //cout << "before print computer board";
         printBoard(boardSizeIn, boardSize, A);
          
         if(checkForWin(A, boardSizeIn, 2)){
            break;
         }
     }
      
     
     checkForWin(A, boardSizeIn, 1);
     checkForWin(A, boardSizeIn, 2);

      if(checkForWin(A, boardSizeIn, 2)){
         cout<< "7 Year Old Wins";
      }else{
         cout<< "User Wins";
      }

     cout << "\n\nProgram ends \n" ;
	return 0;
}


