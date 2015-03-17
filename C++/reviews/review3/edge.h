#ifndef EDGE_H
#define EDGE_H

using namespace std;

enum color{Red, Blue, Green, Empty};

class Edge{
    private:
        // Dist between nodes
        double dist;
        // Edge color
        int color;        

    public:

// Constructor for edge
        Edge (){
            dist = 0.0;
            color = 0;
        }

// Input the color and set it
        void setColor(int col){
            color = col;
        }
    
// Return color
    int getColor(){
        return color;
    }

// Distance is set to d
        void setDist(double d) {
            dist = d;
        }
    
// Return Distance for paths
    double getDist(){
        return dist;
    }
};

#endif

