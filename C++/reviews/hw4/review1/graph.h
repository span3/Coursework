#ifndef GRAPH_H
#define GRAPH_H
#pragma once
#define _CRT_RAND_S
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>


using namespace std;

class Graph {

	public:
		Graph(int n = 0);
		~Graph();
    
    	enum COLORS { WHITE, BLACK, NONE };
	int getOrder() {return order;};
	int getSize() {return size;};

	//edge color back == 0, red == 1, both == 2
	//vertex color back == 0, grey == 1, white == 2
	bool addEdge(int u, int v, double distance = 1.0, int edgeColor = 0);
	bool testEdge(int u, int v);

	void addRandom(double density, int distance);
	void getShortestDist(int u, int edgeColor = 2);
	double getAverageDist(int edgeColor = 2);
   	void readGraph();
   	void sortEdges();
   	void getMST();
  	void initializeVerts();
   	void printBoard();
   	bool playerMove(int x, int y);
  	bool computerMove(int turn);
   	bool pie_rule(int x, int y);
	void check_adjacent(int x, int y);
	void checkWin(COLORS c);
    //bool game_win;
	bool p_win;
    	bool c_win;

	private:
		int TOP, BOTTOM, LEFT, RIGHT;
		struct Edge
		{
			double distance;
			int color; //0 = unexplored, 1 = explored, 2 = discovery, 3 = back
			int v1, v2;
          		bool inTree; //variable used to keep track of edges in the MST
		};

		struct Vertex
		{
			int color; // 0 = unexplored, 1 = explored
			vector<Edge> neighbors;
			vector<int> adjacent;
			double distance;
            		double sub_id;
		};
    
		int order; //number of vertices
		int size; //number of edges
		vector<Vertex> vertices; //vertices in graph = vector of nodes
        	vector<Edge> edgeList; //list of all edges
        	vector< vector<COLORS> > board; //this 2d vector represents the game board	
		void checkWin_rec(int s, int e);
		bool isWhite();
		int getLowestDist();
		bool goodColor(int edgeColor, int testColor);
		
		
};

#endif
