//Graph.cpp

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <list>
#include <vector>

#include "Graph.h"
using namespace std;

void Graph::initGraph(int maxSize){
  //  Graph G = new Graph();
  setMax(maxSize);
  setSize(0);
  //  initMatrix(maxSize);
  //initNodes(maxSize);
  //initList(maxSize);
  return;
}
/*
void Graph::initMatrix(int matSize){
  Edge*** edges = new Edge** [matSize+1];
  for(int x = 1; x <= matSize; x++){
    edges[x] = new Edge*[matSize+1];
  }
  for(int x = 1; x <= matSize; x++){
    for(int y = 1; y <= matSize; y++){
      edges[x][y] = NULL;
    }
  }
  matrix = edges;
}
*/

/*
void Graph::initList(int maxSize){
  list** l = new list*[maxSize+1];
  for(int x = 1; x <= maxSize; x++){
    l[x] = new list*[maxSize+1];
  }
  for(int x = 1; x <= maxSize; x++){
    for(int y = 1; y <= maxSize; y++){
      l[x][y] = new list;
    }
  }
  nodeList = l;
  return;
}


void Graph::initNodes(int maxSize){
  Node*** n = new Node**[maxSize+1];
  for(int x = 1; x <= maxSize; x++){
    n[x] = new Node*[maxSize+1];
  }
  for(int x = 1; x <= maxSize; x++){
    for(int y = 1; y <= maxSize; y++){
      n[x][y] = NULL;
    }
  }

  nodes = n;
}
*/
/*
void Graph::fillGraph(double edgeDensity, int distRange){
  edgeDensity = edgeDensity*100;
  edgeDensity = edgeDensity+0.5;
  int chance = (int)edgeDensity;
  for(int x = 1; x <= getMax(); x++){
    for(int y = 1; y <= getMax(); y++){
      if(x != y){
	int e = rand() %100+1;
	int d = rand() %distRange+1;
	int c = rand() %1;
	if(e <= chance){
	  add(x, y, d, c);
	}
      }
    }
  }
}
*/
void Graph::fullHexGraph(){
  int nodeID = 1;
  nodes.resize(max+1);
  for(int x = 1; x <= max; x++){
    nodes[x].resize(max+1);
  }
  //make all of the nodes

  for(int x = 1; x <= max; x++){
    for(int y = 1; y <= max; y++){
      nodes[x][y].setID(nodeID);
      nodes[x][y].setColor(grey);
      nodes[x][y].setSeen(white);
//      cout << "Made node " << nodeID << " from " << x << " " << y << endl;
      size++;
      nodeID++;
    }
  }

  //  cout << "Created " << size << " nodes\n";

  //make all the edges
  nodeList.resize(max+1);
  for(int x = 1; x <= max; x++){
    nodeList[x].resize(max+1);
  }

  for(int x = 1; x <= max; x++){
    for(int y = 1; y <= max; y++){
      if(x > 1 && x < max){
	if(y > 1 && y < max){
	  //set edges for inner node
	  nodeList[x][y].resize(7);
	  add(x, y, x, y-1);
	  add(x, y, x+1, y-1);
	  add(x, y, x-1, y);
	  add(x, y, x+1, y);
	  add(x, y, x-1, y+1);
	  add(x, y, x, y+1);
	}
      }else if(x == 1){
	if(y > 1 && y < max){
	  //set edges for left side node
	  nodeList[x][y].resize(5);
	  add(x, y, x, y-1);
	  add(x, y, x, y+1);
	  add(x, y, x+1, y-1);
	  add(x, y, x+1, y);
	}else if(y == 1){
	  //set (1,1) node edges
	  nodeList[x][y].resize(3);
	  add(x, y, x, y+1);
	  add(x, y, x+1, y);
	}else if(y == max){
	  //set (1, max) node edges
	  nodeList[x][y].resize(4);
	  add(x, y, x, y-1);
	  add(x, y, x+1, y);
	  add(x, y, x+1, y-1);
	}
      }else if(x == max){
	if(y > 1 && y < max){
	  //set edges for right side node
	  nodeList[x][y].resize(5);
	  add(x, y, x, y-1);
	  add(x, y, x, y+1);
	  add(x, y, x-1, y);
	  add(x, y, x-1, y+1);	  
	}else if(y == 1){
	  //set (max, 1) node edges
	  nodeList[x][y].resize(4);
	  add(x, y, x, y+1);
	  add(x, y, x-1, y);
	  add(x, y, x-1, y+1);
	}else if(y == max){
	  //set (max, max) node edges
	  nodeList[x][y].resize(3);
	  add(x, y, x, y-1);
	  add(x, y, x-1, y);
	}
      }else if(y == 1){
	if(x > 1 && x < max){
	  //set edges for top node
	  nodeList[x][y].resize(5);
	  add(x, y, x+1, y);
	  add(x, y, x-1, y);
	  add(x, y, x-1, y+1);
	  add(x, y, x, y+1);
	}
      }else if(y == max){
	if(x > 1 && x < max){
	  //set bottom nodes
	  nodeList[x][y].resize(5);
	  add(x, y, x+1, y);
	  add(x, y, x-1, y);
	  add(x, y, x, y-1);
	  add(x, y, x+1, y-1);
	}
      }
    }
  }
  return;
}

void Graph::printBoard(){
  cout << "  ";
  for(int x = 1; x <= max; x++){
    if(x < 9){
      cout << x << "   ";
    }else{
      cout << x << "  ";
    }
  }
  cout << endl;

  for(int y = 1; y <= max; y++){
    if(y <= 9){
      cout << y << " ";
    }else{
      cout << y;
    }
    for (int z = 1; z < y; z++){
	cout << "  ";
    }
    for(int x = 1; x <= max; x++){
      if(nodes[x][y].getColor() == grey){
	cout << "0   ";
      }else if(nodes[x][y].getColor() == black){
	cout << "B   ";
      }else if(nodes[x][y].getColor() == white){
	cout << "W   ";
      }
    }
    cout << endl;
  }
  return;
}

/*
void Graph::printMatrix(){
  if(isEmpty() == false){
    cout << "Edge Matrix\n";
    cout << "-----------\n";
    for(int x = 1; x <= max; x++){
      for(int y = 1; y <= max; y++){
	if(matrix[x][y] != NULL){
	  cout << " 1 ";
	}else{
	  cout << " - ";
	}
      }
      cout << "\n";
    }
  }else{
    cout << "--->ERROR: Graph Empty, nothing to print\n";
  }
}
*/
/*  
void Graph::freeGraph(Graph G){
  if(isEmpty(G)){
    delete(G);
    return;
  }else{
    //delete edges
    for(int x = 0; x <= G->size; x++){
      for(int y = 0; y <= G->size; y++){
	if(G->matrix[x][y] != NULL){
	  deleteEdge(x, y, G->matrix);
	}
      }
    }
    //delete nodes
    for(int x = 0; x <= G->size; x++){
      freeNode(x, G);
    }
    delete(G);
    return;
  }
}
*/
bool Graph::adjacent(int x, int y, int a, int b){
  for(unsigned int i = 1; i <= nodeList.size()+1; i++){
    if(nodeList[x][y][i] == nodes[a][b].getID()){
      return true;
    }
  }
  return false;
}


bool Graph:: isEmpty(){
  if(size == 0){
    return true;
  }else{
    return false;
  }
}

bool Graph:: isFull(){
  if(size == max*max){
    return true;
  }else{
    return false;
  }
}


void Graph::add(int a, int b, int x, int y){
  if(adjacent(a, b, x, y) == false){
    //    cout << "Adding edge from: " << nodes[a][b].getID() << " to "
    //	 << nodes[x][y].getID() << endl;
    Edge firstEdge; 
    Edge secondEdge;
    firstEdge.setFrom(nodes[a][b]);
    firstEdge.setTo(nodes[x][y]);
    //set list
    nodeList[x][y].push_back(nodes[a][b].getID());
    secondEdge.setFrom(nodes[x][y]);
    secondEdge.setTo(nodes[a][b]);
    //set list
    nodeList[a][b].push_back(nodes[x][y].getID());
    return;
  }else{
    return;
  }
}

void Graph::colorNode(int x, int y, Color c){
  nodes[x][y].setColor(c);
  return;
}

void Graph::colorSeen(int x, int y, Color c){
  nodes[x][y].setSeen(c);
  return;
}

void Graph::deleteEdge(int a, int b, int x, int y){
  if(adjacent(a, b, x, y) == true){
    //remove from list
  }else{
    return;
  }
}

/*
void Graph::createNode(int id, int x, int y){
  if(!isFull()){
    Node newNode;
    newNode.setID(id);
    nodes[x][y] = &newNode;
    return;
  }else{
    return;
  }
}
*/
/*
void Graph::freeNode(int id){
  if(id == G->size){
    delete G->nodes[id];
    G->nodes[id] = NULL;
    G->size--;
    return;
  }
}

int Graph::getEdgeDist(Node x, Node y, Edge* matrix[][]){
  return &matrix[x][y]->dist;
}

void Graph::setEdgeDist(Node x, Node y, Edge* matrix[][], int d){
  matrix[x][y]->dist = d;
  return;
}

int Graph::getEdgeColor(Node x, Node y, Edge* matrix[][]){
  return &matrix[x][y]->color;
}

int Graph::setEdgeColor(Node x, Node y, Edge* matrix[][]){
  matrix[x][y]->color = c;
  return;
}
*/
