/********************************************************************************************
  After making this dijkstras program I learned the importance of object orientented design.
  Using OO design makes declaring, initializing and modifying abstract data types much
  more easier. Making the graph, node and edge classes help me understand the importance of
  private variables, public variables and information hiding. Information hiding goes hand
  in hand with accessor functions. When data is private, but you still need small access 
  you need to use access functions that return the desired information. For a good ADT
  class you need accessor functions, manipulation functions that changes data in the ADT,
  constructors that initialize the ADT to a certain state, destructors that free information
  once the data is out of scope and finally print functions to allow the user to read
  information in the ADT. Print functions are also essential to debugging the ADT also.
  When using random you should only seed once in the entire program or else you will get
  the same random number every second. Using the time as a seed gives you a psuedo random
  result thats good enough for testing but should be changed on a real program.
  
  How to compile: 
    > g++ -o dijkstra graph.cpp
  How to Run
    > dijkstra
 ******************************************************************************************/
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <cmath>

using namespace std;

//converts an int into a string
string convertInt(int number){
  stringstream ss;  //create a stringstream
  ss << number;  //add number to the stream
  return ss.str();  //return a string with the contents of the stream
}

//returns random number from min to max if see
int random_int(int min, int max){
  return (rand()%((max+1)-min))+min;
}

//enum for the status of a node
enum Status{
  NOT_VISITED,
  VISITED
};

//forward declaration in order to use a node object in edge
class Node;

//A single Edge (connection) on a graph
class Edge{
  private:
  Node* firstNode;  //originating vertex
  Node* secondNode;  //destination vertex
  unsigned cost;  //cost of edge assuming positive
  string color;
  
  public:
  //Constructor
  Edge(Node *inFirstNode, Node *inSecondNode, unsigned incost, string incolor){
    firstNode = inFirstNode;
	secondNode = inSecondNode;
	cost = incost;
	color = incolor;
  }
  
  //Access functions
  Node* getFirstNode(){ return firstNode; }
  Node* getSecondNode(){ return secondNode; }
  unsigned getCost(){ return cost; }
  string getColor(){ return color; }
};

//An object that holds the vertex of a graph and its connections
class Node{
  private:
  string name;               //Name of node
  string color;              //used for dicovery status
  int distance;              //distance from source
  enum Status status;        //enum to check if node has been visited
  
  public:
  vector<Edge> adjNodeList;  //list of connected vertices to this
  //Constructor
  Node(string id){ 
    name = id;
    status = NOT_VISITED;	
  }
  //Destructor called when object is out of scope
  ~Node(){ adjNodeList.clear(); }
  
  //Manipulation functions
  void setStatus(enum Status st){ status = st; }
  void setDistance(int dist){ distance = dist; }
  void setColor(string color){ this->color = color; }
  
  void addAdjNode(Node* adj, unsigned cost, string color){
    Edge newEdge = Edge(this, adj, cost, color);
	adjNodeList.push_back(newEdge);
  }

  //Access functions
  string getName(){ return name; }    //returns name of Node
  string getColor(){ return color; }  //return clor status of node
  vector<Edge>& getAdjNodeList(){ return adjNodeList; }  //returns adjacent node list
  int getDistance(){ return distance; }
  
  //Print functions
  void displayList(){
    string edgeOp = "->";
	for(int i = 0; i < adjNodeList.size() ; i++){
	  Edge edg = adjNodeList[i];
	  cout << name << "->" << edg.getSecondNode()->getName() << endl;
	}
  }
};
  
//Undirected graph object
class Graph{
  private:
  bool foundCycle;
  int desiredCycSize;
  int size, weightRange;
  double density;
  
  public:
  vector<Node*> nodeList;  //List of vertices
  
  //Constructor
  Graph(int graphSize, double density, int weightRange){
    //populates the graph with nodes
    for( int i = 0; i < graphSize; i++){
      string nodeId = "node_" + convertInt(i);
	  Node* temp = new Node( nodeId );
	  this->addNewNode(temp);
    }
	this->size = graphSize;
	this->density = density;
	this->weightRange = weightRange;
	
	int connectAmount = ceil(size*.5*(size-1)*density);  //calculates the amount of connections need to be made
	
	int connectFromIndex, connectToIndex; //used to choose 2 random nodes in the graph and connect them.
	for( int i = 0; i < connectAmount; i++){
	  do{
	      connectFromIndex = random_int(0, nodeList.size()-1);
	      connectToIndex = random_int(0, nodeList.size()-1);
		}while (connectFromIndex == connectToIndex);  //makes sure the 2 random nodes are not the same node

	 
	  string compareFrom, compareTo;  //used to compare pre-existing edges to attempted edge
	  bool identicalEdge = false;     //flag used if there is an identical pre-existing edge
	  
	  //Iterates though pre-existing edges comparing them to attempted edge
	  for(int j = 0; j < nodeList[connectFromIndex]->adjNodeList.size() ; j++){
		 compareFrom = nodeList[connectFromIndex]->adjNodeList[j].getSecondNode()->getName();  //gets the names of the nodes that you are already connected to
	     compareTo = nodeList[connectToIndex]->getName();  //gets the name from the node you are trying to connect to
	     
		 if (compareFrom.compare(compareTo) == 0){   //goes in only when an identical edge is found
		   identicalEdge = true;
		   i--;
         }
	  }
	  
	  // If no pre-Existing edges match this new edge then connect the nodes 
	  if (identicalEdge == false){
	    //picks a random color 
	    string color;
	    if( random_int(0,1) == 0) color = "black";
	    else color = "red";
	  
	    //chooses a random weight between 1 and the specified weightRange
	    int weight = random_int(1, weightRange);
	  
	    //makes an "arch" or double sided connection
	    nodeList[connectFromIndex]->addAdjNode(nodeList[connectToIndex], weight, color);
	    nodeList[connectToIndex]->addAdjNode(nodeList[connectFromIndex], weight, color);
	  }
	} // exits when enough connections satisfy the graph density
	
    foundCycle = false; 
  }
  
  //Destructor
  ~Graph(){ 
    //frees memory allocated to the vertices
    for(int i = 0; i < nodeList.size(); i++) delete nodeList[i];
    nodeList.clear();
  } 
  
  //Manipulation functions
  void clearVisited(){
    for(int i = 0; i < nodeList.size() && !foundCycle; i++){
	  nodeList[i]->setStatus(NOT_VISITED);
	}
  }
  
  void addNewNode(Node* nNode){ nodeList.push_back(nNode); } //pushes new node into the nodeList
   
  // Access functions
  
  Node* findByName(string name){
    for(int i = 0; i < nodeList.size(); i++){
	  if(nodeList[i]->getName() == name) return nodeList[i]; //returns node with same name if found
	}
	return NULL;
  }
  
  int getSize(){ return nodeList.size(); }
  string getNameOfIndex(int index){ return nodeList[index]->getName(); }
  
  void printGraph(){
    for( int i; i < nodeList.size(); i++){
	  Node* temp = nodeList[i];
	  cout << temp->getName() << " distance from root is " << temp->getDistance() << endl;
	}
  }
  
  void printAverage(){
    double sum = 0.0, total= nodeList.size();
    double average;
	for( int i = 0; i < nodeList.size(); i++){
	  Node* temp = nodeList[i];
	  if( temp->getDistance() != 99999){  //exludes the none reachable nodes
	    sum += temp->getDistance();
      }
	  else{ total --; }                   //adjusts the amount
	}
	average = sum/total;
	cout << "The sum of all distances is " << sum << "." << endl;
	cout << "The total amount of nodes taken into consideration is " << total << "." <<endl;
	cout << "The average quickest distance it takes to get to any node is " << average << "." <<  endl;
  }
  
 
};

int dijkstra(Graph* graph, int source){
  int i,tmp;
  for ( i = 0; i < graph->getSize(); i++){
    graph->nodeList[i]->setColor("w");
	graph->nodeList[i]->setDistance(99999);
  }
  graph->nodeList[source]->setColor("g");
  graph->nodeList[source]->setDistance(0);
  list<Node*> Q;
  Q.push_back(graph->nodeList[source]);
  while(Q.size() != 0){
    Node* u = Q.front();
	Q.pop_front();
	if (u->getDistance() == -1) break;
	for ( vector<Edge>::iterator e = u->adjNodeList.begin(); e != u->adjNodeList.end(); ++e){ //iterates though current nodes adjacency list
	  Node* v = e->getSecondNode();
	  if ( v->getColor().compare("w") == 0){
	    v->setColor("g");
		if( u->getDistance()+e->getCost() < v->getDistance()){ //checks to see if current path cost is smaller
		  v->setDistance( u->getDistance()+e->getCost() ); //sets the distance to the node
		}
		Q.push_back(v);
	  }	  
	}
	u->setColor("b");
  }
}

int dijkstraColor(Graph* graph, int source, string color){
  int i,tmp;
  for ( i = 0; i < graph->getSize(); i++){
    graph->nodeList[i]->setColor("w");
	graph->nodeList[i]->setDistance(99999);
  }
  graph->nodeList[source]->setColor("g");
  graph->nodeList[source]->setDistance(0);
  list<Node*> Q;
  Q.push_back(graph->nodeList[source]);
  while(Q.size() != 0){
    Node* u = Q.front();
	Q.pop_front();
	if (u->getDistance() == -1) break;
	for ( vector<Edge>::iterator e = u->adjNodeList.begin(); e != u->adjNodeList.end(); ++e){ //iterates though current nodes adjacency list
	  Node* v = e->getSecondNode();
	  if ( e->getColor().compare(color) == 0){
	    if ( v->getColor().compare("w") == 0){
	      v->setColor("g");
		  if( u->getDistance()+e->getCost() < v->getDistance()){ //checks to see if current path cost is smaller
		    v->setDistance( u->getDistance()+e->getCost() ); //sets the distance to the node
		  }
		  Q.push_back(v);
	    }
      }		
	}
	u->setColor("b");
  }
}


int main(){
  //sets the seed for the random calculations
  srand(time(NULL));
  
  //cout << "enter Graph size ";
  //int graphSize;
  //cin >> graphSize;
  //int graphSize = rand()%50+1;
  int graphSize = 50;

  Graph* poop = new Graph(graphSize, .2, 10);
  
  dijkstra( poop, 0);
  cout << endl <<"******** Statistics for a graph with an order of 50 and a density of 0.2. ***********" << endl; 
  poop->printAverage();
  
  cout<< endl<< "**************** using black edges only *****************" << endl;
  
  dijkstraColor( poop, 0, "black");
  poop->printAverage();
  
  cout<< endl << "**************** using red edges only *****************" << endl;
  
  dijkstraColor( poop, 0, "red");
  poop->printAverage();
  
  //Using a graph of density .04
  cout << endl << "******** Statistics for a graph with an order of 50 and a density of 0.4. ***********" << endl; 
  poop = new Graph(graphSize, .4, 10);
  
  dijkstra( poop, 0);
  poop->printAverage();
  
  cout<< endl<< "**************** using black edges only *****************" << endl;
  
  dijkstraColor( poop, 0, "black");
  poop->printAverage();
  
  cout<< endl<< "**************** using red edges only *****************" << endl;
  
  dijkstraColor( poop, 0, "red");
  poop->printAverage(); 
  
}
