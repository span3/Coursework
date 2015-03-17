//Graph.h
//Graph ADT Header File
#include <list>
#include <vector>

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

enum Color {grey, black, white};

class Node{
  int id;
  Color color;
  Color seen;
 public:
  Node(){};
  void setID(int nodeID){id = nodeID;};
  int getID(){return id;};
  void setColor(Color c){color = c;};
  Color getColor(){return color;};
  void setSeen(Color c){seen = c;};
  Color getSeen(){return seen;};
};

class Edge{
  // 0 = black 1 = red
  Node from;
  Node to;
  
 public:
  Edge(){};
  void setFrom(Node inFrom){from = inFrom;};
  void setTo(Node inTo){to = inTo;};
  Node getFrom(){return from;};
  Node getTo(){return to;};
};

class Graph{
 private:
  int max;
  int size;

 public:
  Graph(){};
  vector< vector< vector<int>  > > nodeList;
  vector< vector<Node> > nodes;
  //getters and setters for private variables
  void setMax(int maxSize){max = maxSize;};
  int getMax(){return max;};
  void setSize(int s){size = s;};
  int getSize(){return size;};

  //initilization functions
  void initGraph(int maxSize);
  void initList(int maxSize);
  void initNodes(int maxSize);

  //ADT opperations
  void add(int a, int b, int x, int y);
  //pre: !adjacent(a, b, x, y)
  // add undirected edge to nodes (a, b) and (x, y)
  void deleteEdge(int a, int b, int x, int y);
  //pre: adjacent(a, b, x, y)
  // remove undirected edge to nodes (a, b) and (x, y)
  void createNode(int id);
  //pre: !isFull
  //post: !isEmpty(G)
  //make new node
  bool adjacent(int x, int y, int a, int b);
  //Check if two nodes (a, b) and (x, y) are adjacent
  bool isEmpty();
  //check if graph has no nodes
  bool isFull();
  //check if # of nodes is equal to max

  void colorNode(int x, int y, Color c);
  //set color to represent token placement
  void colorSeen(int x, int y, Color c);
  //set color for use in DFS

  void fullHexGraph();
  //Create hex board given size of graph
  void printBoard();
  //print hex board showing player/AI moves
};


#endif
