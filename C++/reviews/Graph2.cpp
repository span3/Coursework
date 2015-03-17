#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream> //contains ifstream
#include <sstream> //contains istringstream
#include <cstring>
#include <climits> //contains INT_MAX
#define size 21 //only used to initialize array sizes
using namespace std;

class Graph {
public:

   Graph (int rgb) //Constructor that reads in graph from file
   { 
      ifstream myfile ("graph_data.txt");
      //ifstream myfile ("Mstdata.txt");
      string line;
      if (myfile.is_open()) {
         getline (myfile, line);
         //Grabs the node size from file
         //Converts line first to a C string and then converts that into an int
         graph_size = atoi (line.c_str()); 
         
         init_graph(); //calls function that initializes graph values to 0

         while (myfile.good())
		{
			if (myfile.eof()) {
				break;
			}
			getline (myfile,line);
			char* line_cstr = new char [line.length()+1];
			//Stores a C string copy of line in line_cstr
			strcpy (line_cstr, line.c_str()); 
			//Splits the C string line into tokens separated by spaces
			char* line_char = strtok (line_cstr," ");
			while (line_char != 0) 
            {
               //Stores each integer in their respective variable
			    node_i = atoi(line_char);
				line_char = strtok(NULL," ");
                
                node_j = atoi(line_char);
				line_char = strtok(NULL," ");
                
                weight = atoi(line_char);
				line_char = strtok(NULL," ");
                
                color = atoi(line_char);
				line_char = strtok(NULL," ");
                
                //Fills in the values for weight and color into the graph
                make_graph (); 
            }
         }
         
         prim(rgb);
         //print_graph();
         
      }
      myfile.close();
   };

   /************** Create the graph ***************/
   void init_graph () {
      //Initializes the graph matrix slots to 0
      for (int i = 0; i < graph_size; i++){
         for (int j = 0; j < graph_size; j++) {
            graph[i][j][0] = 0; //[0] will hold weight
            graph[i][j][1] = 0; //[1] will hold color
         }
      }
   }

   //Fills in graph matrix with values from the file
   void make_graph () {
      graph[node_i][node_j][0] = graph[node_j][node_i][0] = weight;
      graph[node_i][node_j][1] = graph[node_j][node_i][1] = color;

      //cout << "(" << node_i << ", " << node_j << "): ";
      //cout << "weight: " << graph[node_i][node_j][0]; 
      //cout << " color: " << graph[node_i][node_j][1] << endl;
   }

   /************* Prints out graph **************/
   void print_graph () {
      cout << endl;
      cout << "\nprint_graph()" << endl;
      for (int i = 0; i < graph_size; i++){
         for (int j = 0; j < graph_size; j++) {
            cout << "(" << i << ", " << j << ") :" << graph[i][j][0];
            cout << " "<< graph[i][j][1] <<" "; 
         }
         cout << "\n";
      }
   }

   /********** Determine minimum distance *********/
   int find_min_weight (int dist_fromcurr[], bool in_mst[]) 
   {
      int min_index, min_dist = INT_MAX;
      for (int i = 0; i < size; i++) {
         //cout << "dist_fromcurr[" << i << "] = " << dist_fromcurr[i] << endl;
         if (!in_mst[i] && dist_fromcurr[i] < min_dist) {
            min_dist = dist_fromcurr[i];
            min_index = i;
         }
      }
      return min_index;
   }

   /*********** Prim's Algorithm ***********/
   void prim (int rgb) {
      bool in_mst[size]; 
      int mst_set[size];
      int dist_fromcurr[size];

      //Initializes arrays
      for (int i = 0; i < size; i++) {
         dist_fromcurr[i] = INT_MAX;
         in_mst[i] = false;
         //initializes mst_set to -1 
         mst_set[i] = -1;
      }

      dist_fromcurr[0] = 0; //set first node to 0 so it will be picked first
      int curr_node = 0; //the current node is the first node

      for (int i = 0; i < graph_size; i++) 
      {
         int min_node = find_min_weight(dist_fromcurr,in_mst);
         in_mst[min_node] = true;

         curr_node = min_node;
         //cout << "\ncurr_node: " << curr_node << endl;
         mst_set[i] = curr_node;
         //cout << "mst_set[" << i << "]: " << mst_set[i] << endl;

         //Updates the values in dist_fromcurr[]
         for (int j = 0; j < graph_size; j++) {
            
            if (graph[curr_node][j][0] > 0 && !in_mst[j] && graph[curr_node][j][1] == rgb) {
               if (graph[curr_node][j][0] < dist_fromcurr[j]) {
                  mst_set[j] = curr_node;
                  dist_fromcurr[j] = graph[curr_node][j][0];
                  //cout << "dist_fromcurr[" << j << "] = " << dist_fromcurr[j] << endl;
                  
               }
            }
         }
      }
      print_sum (dist_fromcurr, mst_set); 
   }

   /**************** Prints the MST cost ****************/

   void print_sum (int dist_fromcurr[], int mst_set[]) {
      int sum = 0;
      for (int k = 0; k < graph_size; k++) {
         //cout << "dist_fromcurr[" << k << "] = " << dist_fromcurr[k] << endl;
         //cout << "mst_set[" << k << "] = " << mst_set[k] << endl;
         sum += dist_fromcurr[k];
      }
      cout << "MST = " << sum << endl;
   }
   
      
private: 
   int graph [size][size][2]; 
   int graph_size, node_i, node_j, weight, color;

}; 

int main() {
   cout << "Red edges" << endl;
   Graph* graph1 = new Graph(0);
   cout << "\nGreen edges" << endl;
   Graph* graph2 = new Graph(1);
   cout << "\nBlue edges" << endl;
   Graph* graph3 = new Graph(2);
}




