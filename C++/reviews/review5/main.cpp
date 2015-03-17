
/*main.cpp file */
/*I learned how to use and implement Prim's algorithm.I also learned about time management and how to not underestimate the scope of a program just because we 
know the algoritim. This progrm does not clearly print out the minimal spanning tree info, but it does print out graphs, and before tampering with it, did print out colors. While implementing the algorithm itself was not too difficult, I raN short of time to check why they were not being connected.  
 *
 * This program in particular need to be mapped out with psuedo-code and
 * graph drawings.Some of the functions, such as Dijkstra, were impossible to
 * write on the spot,without seeing exactly how the algorithm runs. This also
 *  helped keep track  of my logic, so that if I had to add in something new,
 *  such as a counter, it was clear where it should go.(Rather than guess and check).
*/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <string>
#include "GraphNode.h"
#include "edge.h"
#include "node.h"

using namespace std;

int main() {
   srand(time(0));    // Seeding generates unique numbers
   char farray[200];
   char cArray[3];
   cout<< "Please type a valid file name yo"<< endl;
   cin >> farray;
   cout<< "Please select a color to use, such as 'rgb' for red, green or blue";
   cin >> cArray;
   cout<<endl;
   GraphNode graph(farray);
   graph.setUp();
   graph.makeColorGraph(cArray,3);
   graph.printDistance(graph.getGraph());
   cout<<endl;
   graph.printColor(graph.getGraph());
   graph.findConnected(graph.getGraph());
   graph.prims();
   if(graph.checking()){
	   cout<< "Total cost = "<<graph.sum()<< endl;
   }else{
	   cout<< "No minimal spanning tree exists. "<< endl;
	   cout<< "Total cost = -1"<<endl;
   }
   graph.deleteGraph();
   // Frees the matrixes
   return 0;
}
