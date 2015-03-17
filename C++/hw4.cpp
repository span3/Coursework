// This program mostly taught me how to implement distance finding algorithms in a practical
// environment.  The hex game was quite simple, though tedious, to set up, due to all the edges
// that needed to be drawn.  It was also quite challenging at first to visualize the positions
// of the nodes within the array, but after a while I grew used to the calculation method.
// Through the course of making this program, I also learned about the game of Hex, and how
// it is played.  While it seems like a well-designed AI is able to beat a human player almost
// all the time, I'm quite interested in what I can come up with on the next programming assignment.
// The fundamentals of the game, where you have to aim to block your opponent out, seem like they
// contain a huge amount of possible plays, and I'm curious as to how the Monte Carlo algorithms will
// handle that.  Unfortunately, I only had time to have the AI make random moves, and wasn't able to 
//split up the graph classes into a seperate header.  These are both things that I want to fix while 
// working on final program.

// To compile: g++ -o hw4 hw4.cpp
// To run: hw4
// Reference used for classes: http://www.cplusplus.com/forum/general/371/

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

//forward declaration in order to use a node object in edge
class Node;

//A single Edge (connection) on a graph
class Edge{
  private:
  Node* firstNode;  //originating vertex
  Node* secondNode;  //destination vertex
  int color;
  
  public:
  //Constructor
  Edge(Node *inFirstNode, Node *inSecondNode, int incolor){
    firstNode = inFirstNode;
	secondNode = inSecondNode;
	color = incolor;
  }
  
  //Access functions
  Node* getFirstNode(){ return firstNode; }
  Node* getSecondNode(){ return secondNode; }
  int getColor(){ return color; }
};

//An object that holds the vertex of a graph and its connections
class Node{
  private:
  int status;       //enum to check if node has been visited
  int num;          //the number of the node in the array.
  int visited;      //whether or not the node has been visited (used in checkDone).
  
  public:
  vector<Edge> adjNodeList;  //list of connected vertices to this
  //Constructor
  Node(int count){
    status = 0;	
	num = count;
	visited = 0;
  }
  //Destructor called when object is out of scope
  ~Node(){ adjNodeList.clear(); }
  
  //Manipulation functions
  void setStatus(int st) { status = st; }
  void setVisited(int vis) { visited = vis; }
  
  void addAdjNode(Node* adj){
    Edge newEdge = Edge(this, adj, 0);
	adjNodeList.push_back(newEdge);
  }
  
  void resetVisited (Node* node) { node->visited = 0; }

  //Access functions
  int getNum() { return num; }
  int getStatus() { return status; }
  int getVisited() { return visited; }

};
  
//Undirected graph object
class Graph{
  private:
  int size;
  bool foundCycle;
  
  public:
  vector<Node*> nodeList;  //List of nodes
  
  //Constructor
  Graph(int graphSize){
    for(int i = 0; i < graphSize*graphSize; i++){
	  Node* temp = new Node(i);
      this->addNewNode(temp);
	}
    this->size = graphSize;
  }
  
  void addNewNode(Node* nNode){ nodeList.push_back(nNode); } //pushes new node into the nodeList
   
  // Access functions
  int getSize() { return size; }
  void printGraph(){
    cout << endl;
	for (int i = 0; i < size; i++) cout << "RR";
	cout << endl;
	int indent = 0;
	for (int i = 0; i < size; i++) {
	  for (int j = 0; j < indent; j++) {
	    cout << " ";
	  }
	  cout << "B ";
	  for (int j = 0; j < size; j++) {
	    if (nodeList[i * size + j]->getStatus() == 1) {
		  cout << "B ";
		}
		else if(nodeList[i * size + j]->getStatus() == 2) {
		  cout <<"R ";
		}
		else {
 	      cout << nodeList[i * size + j]->getStatus() << " ";
		}
	  }
	  cout<< " B";
	  cout << endl;
	  indent++;
	}
	for (int i = 0; i < indent; i++) cout << " ";
	for (int i = 0; i < size; i++) cout << "RR";
	cout << endl << endl;
  }
  
  //Inserts the edge for the nodes (and yes, I know it's very long and ugly).
  void insertEdge() {
    //Edges for the four corners.
    nodeList[0]->addAdjNode(nodeList[1]);
	nodeList[0]->addAdjNode(nodeList[size]);
	nodeList[0]->addAdjNode(nodeList[size+1]);
	nodeList[size-1]->addAdjNode(nodeList[size-2]);
	nodeList[size-1]->addAdjNode(nodeList[size*2-1]);
	nodeList[size-1]->addAdjNode(nodeList[size*2-2]);
	nodeList[size*(size-1)]->addAdjNode(nodeList[size*(size-2)]);
	nodeList[size*(size-1)]->addAdjNode(nodeList[size*(size-2)+1]);
	nodeList[size*(size-1)]->addAdjNode(nodeList[size*(size-1)+1]);
	nodeList[size*size-1]->addAdjNode(nodeList[size*size-2]);
	nodeList[size*size-1]->addAdjNode(nodeList[size*(size-1)-1]);
	nodeList[size*size-1]->addAdjNode(nodeList[size*(size-1)-2]);
	//Edges for top, bottom, left, and right nodes.
	for (int i = 1; i < size-1; i++) {
	  nodeList[i]->addAdjNode(nodeList[i-1]);
	  nodeList[i]->addAdjNode(nodeList[i+1]);
	  nodeList[i]->addAdjNode(nodeList[size+i-1]);
	  nodeList[i]->addAdjNode(nodeList[size+i]);
	  
	  nodeList[size*(i+1)-1]->addAdjNode(nodeList[size*i-1]);
	  nodeList[size*(i+1)-1]->addAdjNode(nodeList[size*(i+1)-2]);
	  nodeList[size*(i+1)-1]->addAdjNode(nodeList[size*(i+2)-2]);
  	  nodeList[size*(i+1)-1]->addAdjNode(nodeList[size*(i+2)-1]);
	  
	  nodeList[size*(size-1)+i]->addAdjNode(nodeList[size*(size-1)]);
	  nodeList[size*(size-1)+i]->addAdjNode(nodeList[size*(size-1)+i+1]);
	  nodeList[size*(size-1)+i]->addAdjNode(nodeList[size*(size-2)+1]);
	  nodeList[size*(size-1)+i]->addAdjNode(nodeList[size*(size-2)+2]);
	  
	  nodeList[size*i]->addAdjNode(nodeList[size*(i-1)]);
	  nodeList[size*i]->addAdjNode(nodeList[size*(i-1)+1]);
	  nodeList[size*i]->addAdjNode(nodeList[size*i+1]);
	  nodeList[size*i]->addAdjNode(nodeList[size*(i+1)]);
	}
	//Edges for remaining nodes.
	for (int i = 1; i < size-1; i++) {
	  for (int j = 1; j < size-1;j++) {
	    nodeList[size*i+j]->addAdjNode(nodeList[size*(i-1)+j]);
		nodeList[size*i+j]->addAdjNode(nodeList[size*(i-1)+j+1]);
		nodeList[size*i+j]->addAdjNode(nodeList[size*i+j-1]);
		nodeList[size*i+j]->addAdjNode(nodeList[size*i+j+1]);
		nodeList[size*i+j]->addAdjNode(nodeList[size*(i+1)+j-1]);
		nodeList[size*i+j]->addAdjNode(nodeList[size*(i+1)+j]);
	  }
	}
  }	
  //Checks to see if a winner is won.
  int checkDone(int playerTurn) {
    int cursor = 0;
    for (int i = 0; i < size; i++) {
      if (playerTurn == 1) {
	    //If a node on the side is filled, start from there.
        if (nodeList[size*i]->getStatus() == 1) {
	      cursor = size*i;
		  int temp;
		  int done = 0;
		  while (done == 0) {
		    temp = cursor;
			int found = 0;
			//Iterate through the edges to see if an adjacent node is filled.
	        for ( vector<Edge>::iterator e = nodeList[cursor]->adjNodeList.begin(); e != nodeList[cursor]->adjNodeList.end(); ++e){
			  if (found == 1) break;
              if( e->getSecondNode()->getStatus() == 1 && e->getSecondNode()->getVisited() == 0) {
 		        cursor = e->getSecondNode()->getNum();
				e->getFirstNode()->setVisited(1);
				found = 1;
				if ( (cursor % size) == size-1) {
				  for (int i = 0; i < size*size; i++) nodeList[i]->setVisited(0);
				  return 1;
				}
			  }
	        }
			if (temp == cursor) {
			  for (int i = 0; i < size*size; i++) nodeList[i]->setVisited(0);
			  return 0;
			}
	      }
	    }
	  }
	  //Same method but for the computer.
      if (playerTurn == 2) {
        if (nodeList[i]->getStatus() == 2) {
	      cursor = i;
		  int temp = cursor;
		  int done = 0;
		  while (done == 0) {
		    int found = 0;
	        for ( vector<Edge>::iterator e = nodeList[cursor]->adjNodeList.begin(); 
	              e != nodeList[cursor]->adjNodeList.end(); ++e){
			  if (found == 1) break;
              if( e->getSecondNode()->getStatus() == 2) {
			    cursor = e->getSecondNode()->getNum();
				e->getFirstNode()->setVisited(1);
				found = 1;
				if ( (cursor >= (size*(size-1))) && (cursor < (size*size)) ) {
				  for (int i = 0; i < size*size; i++) nodeList[i]->setVisited(0);
				  return 2;
				}
			  }
	        }
			if (temp == cursor) {
			  for (int i = 0; i < size*size; i++) nodeList[i]->setVisited(0);
			  return 0;
			}
	      }
	    }
	  }
    }
    return 0;
  }
};

//Prompts player for a move and makes sure the move is valid.
void playerTurn(Graph* graph) {
  int x, y;
  int valid = 0;
  while (valid == 0) {
    do {
      cout << "Enter row coordinate: ";
      cin >> x;
    } while (!cin || x <= 0 || x > graph->getSize());
    do {
	  cout << "Enter col coordinate: ";
	  cin >> y;
    } while (!cin || y <= 0 || y > graph->getSize());
	if (graph->nodeList[(x-1) * graph->getSize() + y-1]->getStatus() == 0) {
	  valid = 1;
      graph->nodeList[(x-1)*graph->getSize() + y-1]->setStatus(1);
	}
	else {
	  cout << "This spot is taken, please enter another" << endl;
	}
  }
}

//The computer makes a random move.
void computerTurn(Graph* graph, int firstTurn, int turnCounter) {
  int x, y, spot;
  int valid = 0;
  int start = 0;
  int player = 1;
  int positions[graph->getSize() * graph->getSize() + 1];
  int max = 0;
  for (int i = 0; i < graph->getSize()*graph->getSize(); i++) positions[i] = 0;
  for (;;) {
    if (graph->nodeList[start]->getStatus() == 0) {
      Graph temp = *graph;
      for (int i = 0; i < 100; i++) {
        for (int j = 0; j < ((graph->getSize()*graph->getSize()) -turnCounter-1) ;j++) {
          while (valid == 0) {
            x = rand() % graph->getSize();
            y = rand() % graph->getSize();
            if (temp.nodeList[ x*graph->getSize() + y]->getStatus() == 0) {
              valid = 1;
              temp.nodeList[ x*graph->getSize() + y]->setStatus(player);
              if (player == 1) player = 0;
              else if (player ==  0) player = 1;
            }
          }
        }
      }
      if (temp.checkDone(0) == 1) positions[start]++;
    }
    else {
      start++;
    }
    if (start > graph->getSize()*graph->getSize()) break;
  }
  for (int i = 0; i < graph->getSize()*graph->getSize();i++) {
    if (positions[i] > max) {
      max = positions[i];
      spot = i;
    }
  }
  graph->nodeList[spot]->setStatus(2);
  if (firstTurn == 1) {
    graph->printGraph();
    int pie;
    do {
      cout << "Enter 1 to switch places, 0 to proceed: ";
   	  cin >> pie;
    } while (!cin || pie < 0 || pie > 1);
    if (pie == 1) {
      graph->nodeList[ x*graph->getSize() + y]->setStatus(1);
	  computerTurn(graph, 0, turnCounter);
	  graph->printGraph();
    }
  }
}

void declareWinner (int winner) {
  if (winner == 1) cout << endl << "You win!!!" << endl;
  else if (winner == 2) cout << endl << "The computer wins...better luck next time" << endl;
  exit(0);
}

int main() {
  srand(time(NULL));
  int sizeOf, choice, pie;
  int firstTurn = 1;
  int done = 0;
  int turnCounter = 0;
  cout << "**********************************************************************" << endl;
  cout << "* Welcome to the game of Hex! Your goal is to form a horizontal line *" << endl;
  cout << "* before your opponent can form a vertical line.                     *" << endl;
  cout << "**********************************************************************" << endl << endl;
  cout << "Enter desired board size: ";
  cin >> sizeOf;
  Graph* graph = new Graph(sizeOf);
  graph->insertEdge();
  graph->printGraph();
  do {
    cout << "Enter 1 to go first, 0 to go second: ";
    cin >> choice;
  } while (!cin || choice < 0 || choice > 1);
  if (choice == 1) {
    firstTurn = 0;
    playerTurn(graph);
    turnCounter++;
    computerTurn(graph,firstTurn, turnCounter);
    turnCounter++;
    graph->printGraph();
  }
  else {
    computerTurn(graph, firstTurn, turnCounter);
    turnCounter++;
    firstTurn = 0;
  }
  while (done == 0) {
    playerTurn(graph);
    turnCounter++;
    if (graph->checkDone(1) == 1) declareWinner(1);
    computerTurn(graph, 0, turnCounter);
    turnCounter++;
    if (graph->checkDone(2) == 2) declareWinner(2);
    graph->printGraph();
  }
  graph->printGraph();
}
