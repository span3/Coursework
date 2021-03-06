//This assignment taught me how to use file input and implement Prim's MST algorithm in C++.
//Also, since I was unable to finish assignment 2 in time, I was able to catch up on learning to use
//the class structure and Object Oriented coding.  The usage of enum to quickly check whether or not
//nodes have been visited was also quiet convenient.  Implementing Prim's algorithm was a lot easier than
//I expected it to be once I had established a solid class for the graph, nodes, and edges used.  By 
//calling methods from them, I was able to save a lot of time and frustration that would otherwise be
//spent keeping track of runaway variables.  The file input in C++ is also a lot more simplified compared
//to C, and simply using the >> operator to directly store values is extremely useful.

//Reference used for classes: http://www.cplusplus.com/forum/general/371/

#include <vector>
#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

//converts an int into a string
string convertInt(int number){
  stringstream ss;  //create a stringstream
  ss << number;  //add number to the stream
  return ss.str();  //return a string with the contents of the stream
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
  void setDistance(int dist){ distance = dist; }
  void setColor(string color){ this->color = color; }
  void setStatus(enum Status st) { status = st; }
  
  void addAdjNode(Node* adj, unsigned cost, string color){
    Edge newEdge = Edge(this, adj, cost, color);
	adjNodeList.push_back(newEdge);
  }

  //Access functions
  string getName(){ return name; }    //returns name of Node
  string getColor(){ return color; }  //return clor status of node
  Status getStatus() { return status; }
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
  int size;
  bool foundCycle;
  
  public:
  vector<Node*> nodeList;  //List of vertices
  
  //Constructor
  Graph(int graphSize){
    for(int i = 0; i < graphSize; i++){
      string nodeId = convertInt(i);
	  Node* temp = new Node( nodeId );
	  this->addNewNode(temp);
    }
    this->size = graphSize;
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
  void addNode(int start, int end, int weight, string color ) {
    nodeList[start]->addAdjNode(nodeList[end],weight,color);
    nodeList[end]->addAdjNode(nodeList[start],weight,color);
  }
   
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
  
};

void MST (Graph* graph, int redChoice, int greenChoice, int blueChoice) {
  int done = 0;  //Variable to check if all nodes have been reached.
  int total = 0;
  int sum = 0;
  int count = 0;
  int min;
  Node* currOne = new Node(" "); //Storage nodes to hold the minimum edge's nodes.
  Node* currTwo = new Node(" ");
  
  //Start by making the first node visited
  graph->nodeList[0]->setStatus(VISITED);
  while (done == 0) {
    min = 100000000;

    //Run through each node list of the graph and check for their adjacent edge lists if the node has already been visited.
    for (int i = 0; i < graph->getSize(); i++) {
      if(graph->nodeList[i]->getStatus()== VISITED) {
        for ( vector<Edge>::iterator e = graph->nodeList[i]->adjNodeList.begin(); e != graph->nodeList[i]->adjNodeList.end(); ++e){
          //Make sure the newfound edge leads to a node we have not visited and has the lowest cost.
          if ( (e->getSecondNode()->getStatus() == NOT_VISITED) && (e->getCost() <= min) ) {
            //Confirm that the color of the edge is correct.
            if ( (e->getColor() == "red" && redChoice == 1) || (e->getColor() == "green" && greenChoice == 1) 
                || e->getColor() == "blue" && blueChoice == 1) {
              min = e->getCost();
              currOne = e->getFirstNode();
              currTwo = e->getSecondNode();
            }
          }
        }
      }
    }
    //Print out the beginning and ending nodes of the smallest edge and its cost.

    graph->findByName(currTwo->getName())->setStatus(VISITED);
    cout << currOne->getName() << " to " << currTwo->getName() << " costs " << min << ", ";
    count++;
    if (count == 5) {
      count = 0;
      cout << endl;
    }

    //Add the cost to the sum
    sum = sum + min;
    total++;
    //Check if every node has been reached.
    done = 1;
    for (int i = 0; i < graph->getSize(); i++) {
      if (graph->nodeList[i]->getStatus() == NOT_VISITED) done = 0;
    }
  }

  //Print out the total cost and average of the MST
  cout << endl << "The total cost is " << sum << endl;
  graph->clearVisited();
}
void createGraph(ifstream& f_in, Graph* graph) {
  int i = 0;
  int sizeOf,start,end,weight,colorFlag;
  string color;
  int** edgeInfo;
  //Takes in numbers from the file, 4 at a time.
  while (f_in.good()) {
    f_in >> start;
    f_in >> end;
    f_in >> weight;
    f_in >> colorFlag;

    //Initialize the color depending on the number passed in, and then add the node.
    if (colorFlag == 0) {
      color = "red";
    }
    else if (colorFlag == 1) {
      color = "green";
    }
    else {
      color = "blue";
    }
    graph->addNode(start,end,weight,color);
    i++;
  }
}

int main(int argc, char** argv) {
  int sizeOf,redFlag,greenFlag,blueFlag;
  ifstream f_in(argv[1]);
  //If file is invalid, tell the user and then exit.
  if (!f_in) {
    cerr << "cannot open " << argv[1] << endl;
    exit(1);
  }
  f_in >> sizeOf;
  Graph* graph = new Graph(sizeOf);
  createGraph(f_in,graph);
  cout << "Use red edges (0 for no, 1 for yes): ";
  cin >> redFlag;
  cout << "Use green edges (0 for no, 1 for yes): ";
  cin >> greenFlag;
  cout << "Use blue edges (0 for no, 1 for yes): ";
  cin >> blueFlag;
  cout << endl;

  MST(graph, redFlag,greenFlag,blueFlag);
}
