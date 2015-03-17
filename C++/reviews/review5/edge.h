#ifndef EDGE_H
#define EDGE_H

using namespace std;

enum color{Red, Green, Blue, Empty};

class Edge{
   private:
       double distance;  // Distance from one node to another
       color colors;        // Color of edge

   public:

// Edge constructor: default constructor
       Edge (){
    	   distance = 0.0;
       }

// Returns color, used for looking for red/black
// only paths.
       int getColor(){
           return colors;
       }

// Set color to and input r. 0 = black, 1 = red,
// 2 = no color
       void setColor(color c){
           colors = c;
       }

// Returns distance, used for calculated the shortest
// path from one node to another.
       double getDistance(){
           return distance;
       }

// Sets distance to x. Used for initial matrix creation.
       void setDistance(double x) {
           distance = x;
       }
};

#endif

