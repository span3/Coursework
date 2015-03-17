//Steven Pan span3@ucsc.edu
//Assignment #2
//References: http://bytes.com/topic/c/answers/685869-graph-adt

#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;

class Edge {  //Edge contains the distance and color
private:
int distance;
int color;

public:
Edge (int dist, int col) {
    distance = dist;
    color = col;
}
};

void makeGraph(int size, double density, int range, vector<vector<Edge> > graph) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if ( (i != j) && (rand() % 100 + 1 < density * 100) ) { //Check if spot is used and density fulfilled
                int randRange = rand() % range + 1;                 //Assign random distance
                int color = rand() % 2 + 1;                         //Assign color
                graph[i][j] = Edge(randRange, color);               //Set both sides of the graph
                graph[j][i] = Edge(randRange, color);
            }
        }
    }
}

void djikstra(vector<vector<Edge> > graph, int size, int colorChoice) {
    int i, k, small; 
    int visited[size];
    int dist[size]; 
  
    for (i = 1; i <= size; ++i) {  //Initialize the values
        dist[i] = 200000000; 
        visited[i] = 0; //element i hasn't been visited
    } 
    dist[1] = 0; 
  
    for (k = 1; k <= size; ++k) { //Run through each entry
        small = -1; 
        for (i = 1; i <= size; ++i) {
            if (!visited[i] && ((small == -1) || (dist[i] < dist[small]))) //Set smallest entry
                small = i; 
        }
        visited[small] = 1; 
  
        for (i = 1; i <= size; ++i) {  //Check for shortest edge
            if (graph[small][i]->distance) {
                if (dist[small] + graph[small][i]->distance < dist[i])  
                    dist[i] = dist[small] + graph[small][i]->distance;
                }
            }
        }
    } 
    
}

main() {
    vector<vector<Edge> > graph;  //A 2d array of Edges, where position 1 is the source and position 2 is the destination.
    int size,range,source,target,colorChoice;
    double density;
    cout<<"Insert Size of Graph:";
    cin>>size;
    cout<<"Insert Edge Density:";
    cin>>density;
    cout<<"Insert Distance Range:";
    cin>>range;
    makeGraph(size,density,range, graph);
    djikstra(graph,size,1);  //Run the algorithm for each color option
    djikstra(graph,size,2);
    djikstra(graph,size,3);
}
