#include <cmath> //Different library conventions
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <strstream>
#include "graph.h"
using namespace std; //Using Namespace

//Edge Class

	   edge::edge(int dist, int colu, int dest){
	      distance = dist;
	      colour = static_cast<col>(colu);
	      destination = dest;
	   }
	   
	   //Getters functions
	   int edge::getCol(){
	      return colour;
	      }
	   
	   int edge::dest(){
	      return destination;
	   }
	   int edge::getDist(){
	      return distance;
	   }
	  
//Vertex Class

	   vertex::vertex(int a){
	      id = a;
	      state = '*';
	      }
	   //Getter   
	   int vertex::getid(){
	      return id;
	   }
	   
	   char vertex::getState(){
	   
	      return state;
	   }
	   
	   bool vertex::edgeExists(int a){
	      for(int i = 0; i<(int)edges.size(); i++){
	         if(edges[i].dest() == a){
	             return true;
	         }
	      }
	      return false;         
	   }
	   
	   //Returns True if there are no edges from array
	   bool vertex::noEdges(){
	      return edges.empty();
	   
	   }
	   
	   //Adds to adjacency list
	   void vertex::addEdge(int dist, int col, int dest){
	      edge e = edge(dist, col, dest);
	      edges.push_back(e);
	   }
	   
	   //Debug function
	   void vertex::printEdge(){
	       for(int i = 0; i < (int)edges.size(); i++){
	         cout << " Edge to :" << edges[i].dest() << ",";
	         
	      }  
	      cout << "\n";
	   }
	   
	   void vertex::setState(char c){
	      state = c;
	   }
	   


//Class to Store Data during Algorithm

  
   //Getters and Setters
   
   int data::getDist(){
      return dist;
   }
   int data::getPre(){
      return pre;
   }
   
   void data::setDist(int x){
      dist = x;
   }
   
   void data::setPre(int x){
      pre = x;
   }



//Undirected Graph Class
//Uses Previous 3 Classes

	int undirGraph::getSize(){

	  return size;
	}
    
    //Randomly Choose edges
	void undirGraph::edges(float density, int col){
	   int gsize = 0.5*((size*(size -1)*density));
	   int numEdges = 0;
	   int cost = 0;
	   int a = 1, b = 0;
	   int dist;
	   int colour;
	   srand(time(0)); //Ensure True Random
	   //Add nodes until graph has hit density
	   while (numEdges <= gsize){
	      cost = rand() % 10 + 1;
	      a = rand() % size ;
	      b = rand() % size ;
	      while(a==b){
	         a = rand() % size ;
	         b = rand() % size ;    
	      }
	      while(graph[a].edgeExists(b)){
	         b = rand() % size + 1;
	      }
	      dist = rand() % 10 + 1;
	      colour = rand() % 2;
	      graph[a].addEdge(dist, colour, b);
	      graph[b].addEdge(dist, colour, a);
	      
	      //Debug Line
	      //cout << a << "," << b << "\n";
	      numEdges++;
	      
	   }
	}

    //If there is a shorter route to a node than previously known
    //Store that information
	void undirGraph::relax(int a, int b, vector<data>& path, int distance, bool* open){
	   if (path[a].getDist() > path[b].getDist() + distance){
	      path[a].setDist(path[b].getDist() + distance);
	      path[a].setPre(b);
	      open[a] = true;
	      }
	}

    //Return the Node that is the shortest distance from the start
	int undirGraph::findShortest(vector<data>& path, bool* open){
	   int min = 1001;
	   int id = 0;
	   for(int i = 0; i<size; i++){
	      if(path[i].getDist() < min && open[i]){
	          id = i;
	          min = path[i].getDist();
	      }
	   }
	   return id;
	}

    //Find Shortest Path between two nodes
	int undirGraph::shortestPath(int source, int dest){
	   if(graph[dest].noEdges()) return NULL;
	   bool* open = new bool[size];  //Create Visited array
	   vector<data> pathInf;
	   
	   cout << size << endl;
	   for(int i =0;i<size; i++){
	      open[i] = false;
	      pathInf.push_back(data(-1, 1000));
	   }
	   //Start Algorithm   
	   open[source] = true;
	   pathInf[source].setDist(0);
	   
	   int next;
	   next = findShortest(pathInf, open);
	   //While you have not reached the destination
	   while(!open[dest]){
	   
	      next = findShortest(pathInf, open);
	      cout << next << endl;
	      for(vector<edge>::iterator it = graph[next].edges.begin(); it != graph[next].edges.end(); ++it){
	        //Iterate through all paths
	        relax(it->dest(), next, pathInf, it->getDist(), open);
	        
	        open[next] = false;
	      }
	      

	   }
	   for(int i =0;i<size; i++){
	      cout << i << "|" << pathInf[i].getDist() <<" " << pathInf[i].getPre() <<endl;
	   }   
	   return pathInf[dest].getDist();
	}
	
	//Find Shortest Path between two nodes given a colour
	int undirGraph::shortestPath(int source, int dest, int col){
	   if(graph[dest].noEdges()) return NULL;
	   bool* open = new bool[size]; //Create Visited array
	   vector<data> pathInf;
	   
	   
	   for(int i =0;i<size; i++){
	      open[i] = false;
	      pathInf.push_back(data(-1, 1000));
	   }
	      
	   open[source] = true;
	   pathInf[source].setDist(0);
	   
	   int next;
	   while(!open[dest]){
	      next = findShortest(pathInf, open);
	      for(vector<edge>::iterator it = graph[next].edges.begin(); it != graph[next].edges.end(); ++it){
	        if(graph[it->dest()].getState() == '*'){
	            //Iterate through all paths of the right colour
	        	relax(it->dest(), next, pathInf, it->getDist(), open);
	        	open[next] = false;
	        	}
	      }
	   }
	   
	   return pathInf[dest].getDist();
	}
	
	bool undirGraph::allFalse(bool* list){
	       for(int i =0;i<size; i++){
		      if(list[i]){
		         return false;}
		   }
	   return true;
	}
	
	bool undirGraph::isPath(int source, int dest, char c){
		if(graph[dest].noEdges()) return NULL;
		   char save = graph[dest].getState();
		   graph[dest].setState(c);
		   
		   bool* open = new bool[size]; //Create Visited array
		   vector<data> pathInf;
		   
		   
		   for(int i =0;i<size; i++){
		      open[i] = false;
		      pathInf.push_back(data(-1, 1000));
		   }
		      
		   open[source] = true;
		   pathInf[source].setDist(0);
		   
		   int next;
		   while(!open[dest]){
		      
		      if(allFalse(open)) return false;
		      next = findShortest(pathInf, open);
		      open[next] = false;
		      for(vector<edge>::iterator it = graph[next].edges.begin(); it != graph[next].edges.end(); ++it){
		        if(graph[it->dest()].getState() == c){
		            //Iterate through all paths of the right colour
		        	relax(it->dest(), next, pathInf, it->getDist(), open);
		        	
		        	//cout << next << " open";
		        	}
		      }
		   }
		   graph[dest].setState(save);
		   return true;
		}
		
	
	
	
    

    //Construct Undirected Graph
	undirGraph::undirGraph(float density, int col){
	   //Create all the Nodes and Push them into the graph
	   size = 50;
	   for(int i = 0; i<size; i++){
	       vertex v = vertex(i);
	       graph.push_back(v);
	   }
	   edges(density, col);
	}
	
	undirGraph::undirGraph(int s){
	   size = s;
	   for(int i = 0; i<size; i++){
	       vertex v = vertex(i);
	       graph.push_back(v);
	   } 
	
	}
	
	
	//Construct a Object from a file
	undirGraph::undirGraph(ifstream& in){
	   
	   if(in.is_open()){
	      
	      char line[256];
	      in.getline(line, 256);
	      
	      
	      //First line
	      int s, a, b, cost, col;
	      istrstream ist(line);
	      ist >> s >> a >> b >> cost >> col;
	      size = s;

	      for(int i = 0; i<size; i++){
	         vertex v = vertex(i);
	         graph.push_back(v);
	      }
	      //Rest of File 
	      graph[a].addEdge(cost, col, b);
	      while(in.getline(line, 256)){
             istrstream ist(line);
	         ist >> a >> b >> cost >> col;
	         
	         graph[a].addEdge(cost, col, b);
	      
	      }
	      
	      
	   }
	//dumpGraph();
	
	}

    //Debug Function - Dump Edges from each node
	void undirGraph::dumpGraph(){
	   int a;
	   for(int i = 0; i < size ; i++){
	      a = graph[i].getid();
	      cout << a << "|";
	      graph[i].printEdge();
	   }
	}
	
	bool undirGraph::allTrue(bool* open){
	   for(int i = 0; i < size; i++){
	      if(open[i] == false) {
	         return false;}
	   }
	   
	   
	   return true;
	}

	bool undirGraph::connected(){
	   for(int i = 0; i<size; i++){
	      if (graph[i].noEdges()){
	         return false;
	      }
	    }
	   return true;
	}
	
	//Create edges on a graph to make it a Hex Board
	void undirGraph::hexBoard(){
	   //Store Invisible Nodes
	   top = size -4;
	   bottom = size -3;
	   left = size - 2;
	   right = size - 1;
	   sq = sqrt(size - 4);

	   for (int i = 0; i < size - 4; i++)
	       if((i+1)%sq == 0){
	          if(i ==0){
	             graph[i].addEdge(1, 1, i+1);
	             graph[i+1].addEdge(1, 1, i);
	             }else if(i == 10){
	                 }
	             else{
	              graph[i].addEdge(1, 1, i-sq);
	              graph[i-sq].addEdge(1, 1, i);	 
	              }      
	       
	       }
	       else{
	           graph[i].addEdge(1, 1, i+1);
	           graph[i+1].addEdge(1, 1, i);
	           if(i>(sq-1)){
	              graph[i].addEdge(1, 1, i-sq);
	              graph[i-sq].addEdge(1, 1, i);
	              graph[i].addEdge(1, 1, i-(sq-1));
	              graph[i-(sq-1)].addEdge(1, 1, i);
	           }
	       }
	  graph[top].setState('I');
	  graph[bottom].setState('I');
	  graph[left].setState('I');
	  graph[right].setState('I');    
	  //Add Links to 'invisible nodes'     
      for(int i = 0; i < sq; i++){
         graph[i].addEdge(1,1,top);
         graph[top].addEdge(1,1,i);
         graph[i+(sq*(sq-1))].addEdge(1,1,bottom);
         graph[bottom].addEdge(1,1,i+(sq*(sq-1)));
      }
      for(int i = 0; i < top; i = i + sq){
         graph[i].addEdge(1,1,left);
         graph[left].addEdge(1,1,i);
      }
      for(int i = (sq-1); i < top; i = i + sq){
         graph[i].addEdge(1,1,right);
         graph[right].addEdge(1,1,i);
      }
	
	}
	
	//See if a move is legal
	bool undirGraph::available(int i, int j){
	   int num = (i*11) + j;
	   //Check to see move is within Range
	   if(i > (sq - 1) || i < 0 || j > (sq -1) || i < 0){
	   	  return false;
	   }
	   //Check to see if move has already been made
	   if(graph[num].getState() == '*'){ return true;}
	   else{return false;}
	
	}
	
	//Make a Move
	void undirGraph::makeMove(int i, int j, char c){
		//Generate Graph Number
	   int num = (i*11) + j;
	   //Make Move
	   if(graph[num].getState() == '*'){
	      graph[num].setState(c);
	      }else{
	      	//Should never happen due to available
	      cout << "Invalid Move";}
	  
	}
	
	//Output board to screen
	void undirGraph::dumpBoard(){
	   for (int i = 0; i< size -4; i++){
	     if(i%sq == 0){
	        cout << "\n";
	        for(int j = 0; j < i / 11; j++){
	           cout << " ";
	        }
	     }
	   cout << graph[i].getState() << " ";
	   }
	   cout << endl;
	}


