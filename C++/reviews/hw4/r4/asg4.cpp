//Stephen Hutt
// CMPS109 Assignment 4
// For information about how to build and What I learned please see README File


#include <cmath> //Different library conventions
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <strstream>
#include "graph.h"
using namespace std; //Using Namespace

int compx = 0;
int compy = 0;

void userMove(undirGraph& board){
   int x, y;
   
   cin.clear();
   cout << "Please Enter your row " << endl;
   cin >> x;
   cout << "Please Enter your column\n";
   cin >> y;
  

   while(!board.available(x, y)){
      cout << "This is not a valid move.\n" << endl;
      cout << "Please Enter your row " << endl;
      cin >> x;
      cout << "Please Enter your column\n";
      cin >> y;
   }

   board.makeMove(x,y,'B');

}

void compMove(undirGraph& board){
   //cout << compx << " " << compy << endl;
   if(compx > 10){
      compx = 0;
   }
   if(compy > 10){
      compy = 0;
      compx++;
   }   
   
   if(board.available(compy,compx)){
      board.makeMove(compy,compx,'W');
   }else{
      compy++;
      compMove(board);
      return;
      }
   compx++;
}

void playGame(undirGraph& board){
    while(!board.isPath(board.top, board.bottom, 'B') && !board.isPath(board.left, board.right, 'W')){
      userMove(board);
      compMove(board);
      board.dumpBoard();

    }

}

//Generate the Board to a certain size
undirGraph make(int sq){

   int i = sq*sq + 4;
   //cout << i;
   undirGraph k = undirGraph(i);
   k.hexBoard();
   return k;
}


int main(){

   undirGraph k = make(11);

   k.dumpBoard();


   //Opening Instructions
   cout << "User Player is playing Top to Bottom and is Black ('B')" << endl;
   cout << "Computer is playing White ('W')" << endl;
   cout << "Please make your first move:"<< endl;
   //Take Turns
   playGame(k);


   //Output who won
   if(k.isPath(k.top, k.bottom, 'B')){
      cout << "User Wins! \n";
   }
   if(k.isPath(k.left, k.right, 'W')){
      cout << "Computer Wins! \n";
   }

   //End Program 
   return 1;
}
