#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include <cstring>
#include "edge.h"
#include "node.h"

using namespace std;

class Graph{
    private:
        int size;
        double* dist;         // count to handle the shortest path
        Edge** graphMatrix;         // Points to the edge matrix that has colors and dists
        Edge** graphMatrixCopy;    
        Node* nodes;          // Nodes in array
        bool* visited;         // Visited nodes
        bool makeRed, makeGreen, makeBlue; // Sets colors
    

    public:
    
    void setUp() {
        // Set all colors to false to start
		makeRed=false;  
		makeGreen=false;
		makeBlue=false;
		dist = new double[size];
		nodes = new Node[size];
		visited = new bool[size];
	}
    //Takes in the MST txt file into an array
	Graph(char array[]) {
		int count = 0; 
		int i, j, color;
		double weight;
		bool begin = true;
		ifstream filename(array);
		if (filename.is_open()) {
			while (!filename.eof()) { //end of file check
				if (begin) {
					filename >> size;
					begin = false;
					graphMatrix = new Edge*[size];
					graphMatrixCopy = new Edge*[size];
					for (int i = 0; i < size; i++) {
						graphMatrix[i] = new Edge[size];
						graphMatrixCopy[i] = new Edge[size];
					}
				} else if (count % 5 == 0) {
					filename >> i;
					count++;
				} else if (count % 5 == 1) {
					filename >> j;
					count++;
				} else if (count % 5 == 2) {
					filename >> weight;
					count++;
				} else if (count % 5 == 3) {
					filename >> color;
					count++;
				} else if (count % 5 == 4) {
					testColor(color, i, j);
                    
					graphMatrix[j][i].setDist(weight);
					graphMatrix[j][i].setDist(weight);
					count++;
				}
			}

			graphMatrix[i][j].setDist(weight);
			graphMatrix[j][i].setDist(weight);
			filename.close();
		} else {
			cout << "Error: Cannot open file, make sure your file name is correct!";
		}
	}
    

        void drawMatrix(int edgeDensity) {
            // 2 arrays point to the graphMatrix
            graphMatrix = new Edge* [size];
            // Copy it
            graphMatrixCopy = new Edge* [size];  

            // Loop to make 2 Arrays for the edges
            for (int i = 0; i<size; i++){
                    graphMatrix[i] = new Edge[size];      
                    graphMatrixCopy[i] = new Edge[size];
            }

            for (int i = 0; i<size; i++){
                for (int j = 0; j<size; j++){
                    // Generate a random number so we can check for connections
                    double density = (rand()%1000);
                    // Now we can set the dist of connected nodes
                    double dist = (rand()%900)/100.0+1.0;
                    //If nodes are connected set a color!
                    int color = (rand()%2);
                    
                    if (i==j){
                        //Sets distance to INF and gives no color [Empty] if nodes are connecting to same nodes
                        graphMatrix[i][j].setDist(INFINITY);     
                        graphMatrix[i][j].setColor(2);           
                        graphMatrixCopy[i][j].setDist(INFINITY);
                        graphMatrixCopy[i][j].setColor(2);
                    }

                    else if (density < edgeDensity){
                        // Set randomly generated dist and color to connected edges
                        graphMatrix[i][j].setDist(dist);    
                        graphMatrix[j][i].setDist(dist);    
                        graphMatrix[i][j].setColor(color);
                        graphMatrix[j][i].setColor(color);

                        graphMatrixCopy[i][j].setDist(dist);
                        graphMatrixCopy[j][i].setDist(dist);
                        graphMatrixCopy[i][j].setColor(color);
                        graphMatrixCopy[j][i].setColor(color);
                    }

                    else {
                        // If disconnected, set a color, dist is set to INF
                        graphMatrix[i][j].setDist(INFINITY);   
                        graphMatrix[j][i].setDist(INFINITY);  
                        graphMatrix[i][j].setColor(color);
                        graphMatrix[j][i].setColor(color);

                        graphMatrixCopy[i][j].setDist(INFINITY);
                        graphMatrixCopy[j][i].setDist(INFINITY);
                        graphMatrixCopy[i][j].setColor(color);
                        graphMatrixCopy[j][i].setColor(color);
                }
            }
        }
    }

// Keep connected nodes in an array 
    void findConnected(Edge** graphMatrix){
        for (int i = 0; i<size; i++){
            for (int j = 0; j<size; j++){
                if (graphMatrix[i][j].getDist() != INFINITY){
                    nodes[i].inputConnected(j);
                    nodes[i].nextcount();
                }
            }
        }
    }

// Gives us the MatrixCopy
    Edge** getGraphMatrixCopy(){
        return graphMatrixCopy;
    }

// Gieves us GraphMatrix
    Edge** getGraphMatrix(){
        return graphMatrix;
    }


// visited and dist are inialized
    void startDijkstra (){
        for (int i = 0; i<size; i++){
            visited[i]=false;
            dist[i]=INFINITY;
        }
    }

// Free matrix
    void deleteMatrix(){
        delete graphMatrix;
        delete graphMatrixCopy;
    }

    void testColor(int color, int i, int j) {
		//for (int i = i; i < size; i++) {
        if(color==0) {
            graphMatrix[i][j].setColor(Red);
            graphMatrix[j][i].setColor(Red);
        }
        else if(color==1) {
            graphMatrix[i][j].setColor(Green);
            graphMatrix[j][i].setColor(Green);
        }
        else if(color==2) {
            graphMatrix[i][j].setColor(Blue);
            graphMatrix[j][i].setColor(Blue);
        }
        else if(color== 3){
            graphMatrix[i][j].setColor(Empty);
            graphMatrix[j][i].setColor(Empty);
        }
    }
    
	void graphColor(char Array[], int asize) {
		bool makeRed, makeGreen, makeBlue = false;
		setBoolColor(Array, asize);
        
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (makeRed && makeGreen && makeBlue) {
					break;
				}
				else if (makeRed && makeGreen) {
					if (graphMatrix[i][j].getColor() != Red
						&& graphMatrix[i][j].getColor() != Green) {
						graphMatrix[i][j].setDist(INFINITY);
						graphMatrix[j][i].setDist(INFINITY);
						testColor(3, i, j);
                        
					}
				} else if (makeGreen && makeBlue) {
					if (graphMatrix[i][j].getColor() != Green && graphMatrix[i][j].getColor() != Blue) {
						graphMatrix[i][j].setDist(INFINITY);
						graphMatrix[j][i].setDist(INFINITY);
						testColor(3, i, j);
					}
				} else if (makeRed && makeBlue) {
					if (graphMatrix[i][j].getColor() != Red
                        && graphMatrix[i][j].getColor() != Blue) {
						graphMatrix[i][j].setDist(INFINITY);
						graphMatrix[j][i].setDist(INFINITY);
						testColor(3, i, j);
					}
				} else if (makeRed) {
					if (graphMatrix[i][j].getColor() != Red) {
						graphMatrix[i][j].setDist(INFINITY);
						graphMatrix[j][i].setDist(INFINITY);
						testColor(3, i, j);
					}
				} else if (makeGreen) {
					if (graphMatrix[i][j].getColor() != Green) {
						graphMatrix[i][j].setDist(INFINITY);
						graphMatrix[j][i].setDist(INFINITY);
						testColor(3, i, j);
					}
				} else if (makeBlue) {
					if (graphMatrix[i][j].getColor() != Blue)
						graphMatrix[i][j].setDist(INFINITY);
					graphMatrix[j][i].setDist(INFINITY);
					testColor(3, i, j);
                    
				}
			}
		}
	}
    
	void setBoolColor(char Array[], int size) {
		for (int i = 0; i < size; i++) {
			if (Array[i] == 'r') {
				makeRed = true;
			}
			if (Array[i] == 'g') {
				makeGreen = true;
			}
			if (Array[i] == 'b') {
				makeBlue = true;
			}
            
		}
        
	}
    
    
// Finds the shortest path from node i to all connected nodes
    int shortestPath(int i, Edge** graphMatrix){
	int shortest = 100;
	double lowest = INFINITY;
	int count = nodes[i].getCount();
	while(nodes[i].getCount()!=0){
		nodes[i].previouscount();
		if(!nodes[i].getVis()){
			int x = nodes[i].getConnected();
			if(lowest>graphMatrix[i][x].getDist()){
				lowest = graphMatrix[i][x].getDist();
				shortest = x;
            }
        }
    }
    nodes[i].setcount(count);
    return shortest;
    }

// Finds the shortest path based on the contest of the dist[]
    int shortestPath(Edge** graphMatrix){
        double lowest=INFINITY;
        int node;
        for (int i = 0; i<size; i++){
            if (dist[i]<lowest && !visited[i]){
                lowest = dist[i];
                node = i;
            }
        }
        return node;
    }
// Print the matrix showing edge color
    void printColor(Edge** graphMatrix){
        cout << "COLOR GRAPH REPRESENTAION" << endl;
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                cout<<graphMatrix[i][j].getColor()<<" ";
                
            }
            cout << endl;
        }
    }
// Print out graphMatrix
// This shows the distance between nodes
    void printDist(Edge** graphMatrix){
    cout << "PLOT/COST GRAPH REPRESENTAION" << endl;
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                cout<<graphMatrix[i][j].getDist()<<" ";
            }
            cout << endl;
        }
    }
};

#endif
