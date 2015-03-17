#include <cmath> //Different library conventions
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <strstream>
using namespace std;

enum col { RED, GREEN, BLUE};

class edge{
   public:
      int getCol();
      edge(int, int, int);
      int dest();
      int getDist();
      
   private:
       int destination;
	   int distance;
	   enum col colour;

};

class vertex{
	private:   
	   char state;
	   int id;
    public:	   
	   vector<edge> edges;
	   vertex(int a);
	   //Getter   
	   int getid();
	   char getState();
	   bool edgeExists(int);
	   bool noEdges();
       void addEdge(int, int, int);
       void printEdge();
       void setState(char);


};

class data{
   int pre;
   int dist;
   
   public:   
   data(int a, int b):pre(a),dist(b){};
   
   int getDist();
   void setDist(int);
   int getPre();
   void setPre(int);

};

class undirGraph{

	public:
	
    vector<vertex> graph;
	int size;
    int top;
    int bottom;
    int left;
    int right;
    int sq;
	int getSize();
	
       undirGraph(float density, int col);
       undirGraph(int);
       undirGraph(ifstream&);
	   void edges(float density, int col);
	   void relax(int, int, vector<data>&, int, bool*);
	   int findShortest(vector<data>&, bool*);
	   int shortestPath(int , int);
	   int shortestPath(int , int, int);
	   
	   void dumpGraph();
	   bool allTrue(bool* );
	   bool connected();
	   
	   void hexBoard();
	   void dumpBoard();
	   void makeMove(int, int, char);
	   bool allFalse(bool*);
	   bool isPath(int, int, char);
	   bool available(int, int);
	   
	   
	   


};
