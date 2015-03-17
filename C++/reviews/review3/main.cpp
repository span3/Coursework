/*I LEARNED:
In this program, we attempted to add the two methods needed to perform Prim's algorithm on a graph. When researching ways of implementing Prim's algorithm, one of my main concerns was what the major differences are between Prim's and Dijkstra's. Conceptually, Prim's algorithm creates a minimum spanning tree for the graph, where Dijkstra's algorithm finds the shortest path. As far as the implementation is concerned, Prim's algorithm finds a short path and does not compute the total weight of the graph like Dijkstra's. I also learned how to implement fileIO into a C++ program. Instead of using cin, like other programs, this program takes a specific file. FileIO in C++ is very simple, as it only takes a few lines of code to build a simple input/output statement. Initially, we declared the colors as integers, but then found out that we were supposed to declare them as the enum type. This was confusing when we began to implement Prim's algorithm, as integers seemed more logical when we first began coding the assignment. I hope to learn more about implementing the standard template library into my code, as I am still working on my transition from standard C-style coding to C++. 
 */

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include "graph.h"
#include "edge.h"
#include "node.h"

using namespace std;

int main() {
    // seed rand() with time to get random numbers
    srand(time(0));
    // file array from input file
    char farray[200];
    // color array for Red 0, Blue 1, Green 2 or Empty 3 
    char cArray[3];
    cout<< "type MST filename (Mstdata.txt): "<< endl;
    cin >> farray;
    cout<< "For Red, Blue, or Green, please select either: r, b or g: ";
    //Takes in chosen color input by user
    cin >> cArray;
    
    Graph graph(farray);
    graph.setUp();
    graph.graphColor(cArray,3);
    graph.printDist(graph.getGraphMatrix());
    graph.printColor(graph.getGraphMatrix());
    graph.findConnected(graph.getGraphMatrix());
    
    graph.deleteMatrix();                           // Free matrix

    return 0;
}
