//GraphDr.cpp
//

#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
  Graph graph1;
  graph1.initGraph(11);
  cout << "Made new 11x11 graph\n";
  if(graph1.isEmpty() == true){
    cout << "New Graph is empty\n";
  }else{
    cout << "--->ERROR: New Graph not empty\n";
  }
  /*
  graph1.createNode(1);
  cout << "Made new node '1' in graph\n";
  if(graph1.isEmpty() == false){
    cout << "graph no longer empty\n";
  }else{
    cout << "--->ERROR: graph empty after node created\n";
  }
  graph1.createNode(2);
  cout << "Made new node '2' in graph\n";
  graph1.add(1, 2, 5, 0);
  cout << "Made edge from node 1 to 2 with color black and distance 5\n";
  if(graph1.adjacent(1, 2) == true){
    cout << "Node 1 is adjacent to node 2 as expected\n";
  }else{
    cout << "--->ERROR: no edge from node 1 to 2\n";
  }
  graph1.printMatrix();
  if(graph1.adjacent(2, 1) == false){
    cout << "---ERROR: no edge from 2 to 1 when there should be\n";
  }else{
    cout << "Node 2 adjacent to Node 1 as expected\n";
  }
  graph1.deleteEdge(1, 2);
  graph1.printMatrix();
  if(graph1.adjacent(1, 2) == false || graph1.adjacent(2, 1) == false){
    cout << "Node 1 is not adjacent to node 2 as expected after deletion\n";
  }else{
    cout << "--->ERROR: edge from node 1 to 2 not deleted\n";
  }
  */
  cout << "Made full graph ready for Hex playing\n";
  graph1.fullHexGraph();
  graph1.printBoard();
  return 0;
}
