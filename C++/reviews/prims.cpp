/*Write Up:
	This program takes in an input file and makes a graph of vertices. It takes the graph and performs Prim's algorithm on it.
	For me, this assignment seemed significantly harder than the second. I had trouble getting the input file to work accordingly
	and I had trouble remembering and  recognizing how Prim's Algorithm worked. Overall, I think I got most of it working, I have 
	printed out the nodes and printed the average weights of  each of the edges in the graph.I chose to use an adjacency matrix for 
	the assignment because I felt it was easier to manage and to use prim?s on. 
*/
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

//Create our graph class

const int size=20;

class graph {
public: 
 void  makeGraph();
 int matrix[20][20][2];
 
};

void graph::makeGraph() {
//set the filename
 ifstream fin("example.txt");
    string line;
	int my_size,from,to,color,dist;
	//get the number of nodes in the matrix
	if(getline(fin,line)){
		istringstream size_iss(line);
		size_iss>>my_size;
		}
	//initialize the matrix
	for(int i=0;i<my_size;i++){
		for(int j=0;j<my_size;j++){
		matrix[i][j][0]=0;
		matrix[i][j][1]=0;
		}
	}
    while (getline(fin, line)) {
        istringstream tokenizer(line);
        string token;
	//get from
        getline(tokenizer, token, ' ');
        istringstream from_iss(token);
        from_iss >> from;
	//get to
        getline(tokenizer, token, ' ');
		 istringstream to_iss(token);
		to_iss>>to;
	//get distance
        getline(tokenizer, token, ' ');
		istringstream dist_iss(token);
        dist_iss >> dist;
	//get color	
		   getline(tokenizer, token, ' ');
		istringstream color_iss(token);
        color_iss >> color;
	//set matrix values
		matrix[from][to][0]=dist;
		matrix[from][to][1]=color;
		matrix[to][from][0]=dist;
		matrix[from][to][1]=color;		
    }
}

int decreaseWeight(int weight[], bool in_tree[]){
 int min=100000;
 int index;
 for(int i=0;i<size;i++){
	if(in_tree[i]==false && weight[i]<min) {
		min=weight[i];
		index=i;
		}
	}
	return index;
}


void prims(int matrix[size][size][2],int source, int colorPref) {
//R=0, G=1, B=2, R,G=3 , R,B=4 , G,B=5 , R,G,B=6;

//initialize all variables
   int parent[size];
   int weight[size];
   bool in_tree[size];
   	int total=0;
	int mycount=0;
	float average=0;
	string colorChoice="No Color";
   for(int i=0;i <size;i++){
      weight[i]=100000;
	  in_tree[i]=false;
   }
   weight[0]=0;
   parent[0]=-1;
   for(int count=0;count<size-1;count++){
      int x=decreaseWeight(weight,in_tree);
      in_tree[x]=true;
      for(int j=0;j<size;j++){
//in color[] : red=0, green=1, blue=2
//For Red (0)

   if(colorPref==0) {
	colorChoice="Red:";
	  if(matrix[x][j][0] && in_tree[j]==false && matrix[x][j][0]<weight[j] &&matrix[x][j][1]==0) {
		mycount++;
         parent[j]=x;
         weight[j]=matrix[x][j][0];
		 cout<<"(" << x<< "," << j << ") ";
		 total=total+weight[j];
      }
   }
//For Green (1)
   if(colorPref==1) {
   	colorChoice="Green:";

      if(matrix[x][j][0] && in_tree[j]==false && matrix[x][j][0]<weight[j] &&matrix[x][j][1]==1) {
      	mycount++;
         parent[j]=x;
         weight[j]=matrix[x][j][0];
		 cout<<"(" << x<< "," << j << ") ";
		 total=total+weight[j];
      }
   }
//For Blue (2)
   if(colorPref==2) {
   	colorChoice="Blue:";

      if(matrix[x][j][0] && in_tree[j]==false && matrix[x][j][0]<weight[j] &&matrix[x][j][1]==2) {
        mycount++;
         parent[j]=x;
         weight[j]=matrix[x][j][0];
		 cout<<"(" << x<< "," << j << ") ";
		 total=total+weight[j];
      }
    }

//For Red and Green (3)
   if(colorPref==3) {
   	colorChoice="Red and Green:";
      if(matrix[x][j][0] && in_tree[j]==false && matrix[x][j][0]<weight[j] &&(matrix[x][j][1]==0||matrix[x][j][1]==1)) {
       	 mycount++;
         parent[j]=x;
         weight[j]=matrix[x][j][0];
		 cout<<"(" << x<< "," << j << ") ";
		 total=total+weight[j];
      }
   }
// For Red and Blue (4)
   if(colorPref==4) {
      	colorChoice="Red and Blue:";
	if(matrix[x][j][0] && in_tree[j]==false && matrix[x][j][0]<weight[j] &&(matrix[x][j][1]==0||matrix[x][j][1]==2)) {
       	mycount++;
         parent[j]=x;
         weight[j]=matrix[x][j][0];
		 cout<<"(" << x<< "," << j << ") ";
		 total=total+weight[j];
      }
   }
//For Green and Blue (5)
   if(colorPref==5) {
   	colorChoice="Green and Blue:";
      if(matrix[x][j][0] && in_tree[j]==false && matrix[x][j][0]<weight[j] &&(matrix[x][j][1]==1||matrix[x][j][1]==2)) {
       	mycount++;
         parent[j]=x;
         weight[j]=matrix[x][j][0];
		 cout<<"(" << x<< "," << j << ") ";
		 total=total+weight[j];
      }
   }
//For Red,Green and Blue (6)
   if(colorPref==6) {
   	colorChoice="Red and Green and Blue:";
      if(matrix[x][j][0] && in_tree[j]==false && matrix[x][j][0]<weight[j]) {
      	mycount++;
         parent[j]=x;
         weight[j]=matrix[x][j][0];
		 cout<<"(" << x<< "," << j << ") ";
		 total=total+weight[j];
      }
    } 
  }
 }
  cout<<endl;
  cout<<colorChoice;
  average=total/size;
  cout<<average<<endl;
  cout<<endl;
 }

int main(){
//create a graph
   graph myGraph;
//set values of the graph using input file
   myGraph.makeGraph();
//use prim's algorithm for source:0 and each possible color combination
   prims(myGraph.matrix,0,0); 
   prims(myGraph.matrix,0,1);  
   prims(myGraph.matrix,0,2);
   prims(myGraph.matrix,0,3);  
   prims(myGraph.matrix,0,4);
   prims(myGraph.matrix,0,5);  
   prims(myGraph.matrix,0,6);
 } 
