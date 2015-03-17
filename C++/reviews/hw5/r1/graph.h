#include<vector>
#include<set>
#include "node.h"



class Graph
{
	public:
		Graph(int, double);
		Graph(char* inFile);
		Graph(int size); //used for game of hex (ie pass 11, for a 11x11 board)
		Graph();
		Node getNodeAt(int i);
		void printEdges();
		void printNodes();
		void printOffset();
		void dijkstra(Color); //overloaded this method so I can distinguish from colored
		void dijkstra();		// paths and all paths
		void printAvg();
		void resetNodes();
		vector<set<Edge> > kruskal();
		int getSmallest();
		int getSmallestIndex();
		int findSet(vector<set<Node*> > setList, Node& n);
		bool isColoringValid(int x, int y);
		void setColor(int x, int y,Color c);
		bool sentinelPathComplete();
		Color sentinelPathCompleteWithColor();
		bool DFS(int start, int target, Color c);
		int getNumNodes(){return numNodes;}

	private:
		vector<Node> nodes;
		vector<Edge> edges;
		int numNodes;
		int hexSize;
		double density;

};

/*//this is kind of weird, i can't remember why i had to do this, but it works
//This is used to compare edges.
bool operator<(Edge e1, Edge e2) 
{	
	if(e1.getW() != e2.getW())
	{
		return e1.getW() < e2.getW();
	}
	else
	{
		return true;
	}
}*/