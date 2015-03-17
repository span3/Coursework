//Hex.cpp
//
//Notes: to compile type 'make all', type 'Hex.exe' to run, and type 
//'make spotless' to remove .o and .exe files
//
//Write up: Got the majority of the implementation done, but got stuck on
//the win-checking. Wrote a Depth first search algorithm, but it wasn't 
//returning the correct depth fot the color chains. Had I been able to
//do the win condition, I would have focused on better AI. As of now, all
//the AI does is pick a random free node. I probably would have taken a
//defensive approach for the AI, blocking the players moves as they are 
//made. The game is still playable, but one will have to keep track of the
//win condition on their own.
//Overall, I learned a great deal more about c++ structure and made
//my original Graph ADT much more solid: changing my matrix to a list and
//using vectors instead of arrays. I also had fun developing the interface
//which, while much simpler than win-checking or AI, still taught me more
//about c++ input, which I find much simpler and easier than c.

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <sstream>
#include <queue>

#include "Graph.h"


using namespace std;


void inst(){
  //print game instructions
  cout << "Hex is played by 2 players on an 11x11 hexagonal board."
       << endl;
  cout << "Players take turns placing tokens on the board." << endl;
  cout << "The first player to make a chain ";
  cout << "across the board is the winner" << endl;
  cout << "Player 1's chain must go from top to bottom to win." << endl;
  cout << "And Player 2's chain must go from left to right to win." 
       << endl;
  cout << "Player 1 is white, and player 2 is black, with 'W' and 'B'" 
       << endl;
  cout << "represting their tokens respectfully" << endl;
  cout << "To make a move, simply type desired location as 'x y'" << endl;
  cout << "where x is the number accross, and y is the depth." << endl;
  cout << "Have Fun!" << endl;
  return;
}

//recursive depth first search to try and find path
int DFSW(Graph g, int x, int y){
  static int depth = 1;
  g.nodes[x][y].setSeen(grey);
  for(unsigned int z = 1; z <= g.nodeList[x][y].size()+1; z++){
    //    cout << "adjacent = " << g.nodeList[x][y][z] << endl;
    for(int a = 1; a <= g.getMax(); a++){
      for(int b = 1; b <= g.getMax(); b++){
	if (g.nodes[a][b].getID() == g.nodeList[x][y][z]){
	  //	  cout << "Target: " << g.nodes[a][b].getID() 
	  //	       << " nieghbor: " << g.nodeList[x][y][z] << endl;
	  if(g.nodes[a][b].getSeen() == white 
	     && g.nodes[a][b].getColor() == white){
	    if(depth < b){
	      depth = b;
	    }
	    depth = DFSW(g, a, b);
	    return depth;
	  }else{
	    return depth;
	  }
	}
      }
    }
  }
  g.nodes[x][y].setSeen(black);
  return depth;
}

//check for top to bottom win
bool whiteWin(Graph g){
  int depth = 0;
  Color c = white;
  for(int x = 1; x <= g.getMax(); x++){
    for(int y = 1; y <= g.getMax(); y++){
      g.colorSeen(x, y, c);
    }
  }
  for(int x = 1; x <= g.getMax(); x++){
    if(g.nodes[x][1].getColor() == white){
      depth = DFSW(g, x, 1);
      //      cout << "Depth = " << depth << endl;
      //      cout << "column = " << x << endl;
    }
    if(depth == g.getMax()){
      return true;
    }
  }
  return false;
}


Graph playerInput(Graph g){
  int in1;
  int in2;
  int n = 0;
  string s;
  string tmp;
  vector <string> tokens;
  
  cout << "Player 1:";
  getline(cin, s);
  stringstream ss(s);
  //get string in form x y and tokenize it
  while(ss >> tmp){
    tokens.resize(tokens.size()+1);
    tokens[n] = tmp;
    n++;
  }
  //check for correct input, if bad input given, call function again
  if(tokens.size() == 2){
    stringstream convert(tokens[0]);
    convert >> in1;
    if(!convert){
      cout << "conversion failed, input must be integer" << endl;;
      playerInput(g);
      return g;
    }
    if(in1 > g.getMax() || in1 < 0){
      cout << "bad input. input must be two integers between 1 and " 
	   << g.getMax() << endl;
      playerInput(g);
      return g;
    }
    stringstream convert2(tokens[1]);
    convert2 >> in2;
    if(!convert2){
      cout << "conversion failed, input must be integer" << endl;;
      playerInput(g);
      return g;
    }
    if(in1 > g.getMax() || in1 < 0){
      cout << "bad input. input must be two integers between 1 and " 
	   << g.getMax() << endl;
      playerInput(g);
      return g;
    }
    //    cout << "white to:" << in1 << " " << in2 << endl;

    //change node color
    g.colorNode(in1, in2, white);
    return g;
  }else{
    cout << "bad input. should be in form: 'x y'" << endl;
    playerInput(g);
    return g;
  }
}

void startPrompt(){
  string in;
  string start ("start");
  string quit ("quit");
  string hint ("how to");
  cout << endl << "::";
  getline(cin, in);

  if(in.compare(start) == 0){
    //run game
    return;
  }else if(in.compare(hint) == 0){
    inst();
    startPrompt();
    return;
  }else if(in.compare(quit) == 0){
    cout << "Game Over" << endl;
    return;
  }else{
    startPrompt();
    return;
  }
}

//simple random AI 
Graph AI(Graph g){
  int x = rand() %g.getMax()+1;
  int y = rand() %g.getMax()+1;
  if(g.nodes[x][y].getColor() == grey){
    g.colorNode(x, y, black);
    cout << "Player 2 chooses node: " << y << " " << x << endl;
    return g;
  }else{
    AI(g);
    return g;
  }
}


int main(){
  Graph graph1;
  int size = 11;

  cout << "Type 'start' to begin game, 'quit' to exit," << endl;
  cout << "or type 'how To' to see instructions:" << endl;
  graph1.initGraph(size);
  graph1.fullHexGraph();
  graph1.printBoard();
  startPrompt();
  while(!whiteWin(graph1)){
    graph1 = playerInput(graph1);
    graph1 = AI(graph1);
    graph1.printBoard();
  }
  return 0;
}
