#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cassert>
#include <list>
#include <algorithm>

using namespace std;
enum myColor{WHITE, BLACK, EMPTY};

// This class represents a directed graph using adjacency list representation
class Graph{
    public:
        int vert; //number of vertices
        list<int> *elist; // Pointer to an array containing adjacency lists 
        vector<int> whiteset; vector<int> blackset; vector<int> blackstart; vector<int> blackend; 
        vector<int> whitestart; vector<int> whiteend; vector<int> picked;
        int array[13][13], board[13][13];
        Graph(int V);  // Constructor
        void addEdge(int size); // function to add an edge to graph
        bool checkwin(int s, int d, int size, int color);  // returns true if there is a path from s to d
        void print_board(int size);
        bool testwin(int s, int d, int size, int color);
};
 
//make new list with given size
Graph::Graph(int vert){
    this->vert = vert;
    elist = new list<int>[vert];
}
 
//add in the connections to the nodes and put the appropriate nodes to check for win condition in sets
void Graph::addEdge(int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            int node = i*size+j;
            if(node == 0){ //left top corner
                elist[i*size+j].push_back(i*size + j+1); whitestart.push_back(node); 					
                elist[i*size+j].push_back( (i+1)*size + j ); blackstart.push_back(node);				
            } else if(node==size-1){ //right top corner
                elist[i*size+j].push_back(i*size + j-1); blackend.push_back(node);
                elist[i*size+j].push_back( (i+1)*size + j-1 ); whitestart.push_back(node);
                elist[i*size+j].push_back( (i+1)*size + j );
            } else if(node==(size*(size-1))){ //left bottom corner
                elist[i*size+j].push_back( (i-1)*size + j ); blackstart.push_back(node);
                elist[i*size+j].push_back( (i-1)*size + j+1); whiteend.push_back(node);
                elist[i*size+j].push_back(i*size + j+1);
            } else if(node==(size*size-1)){ //right bottom corner
                elist[i*size+j].push_back( (i-1)*size + j ); blackend.push_back(node);				
                elist[i*size+j].push_back(i*size + j-1);whiteend.push_back(node);
            } else if(node > 0 && node < (size-1)){ //top border
                elist[i*size+j].push_back(i*size + j-1); whitestart.push_back(node);					
                elist[i*size+j].push_back(i*size + j+1);
                elist[i*size+j].push_back( (i+1)*size + j-1 );				
                elist[i*size+j].push_back( (i+1)*size + j );
            } else if(node%size == 0){ //left border
                elist[i*size+j].push_back((i-1)*size + j); blackstart.push_back(node);
                elist[i*size+j].push_back(i*size + j+1);
                elist[i*size+j].push_back( (i+1)*size + j );
                elist[i*size+j].push_back( (i+1)*size + j+1 );
            } else if(node%size == (size-1)){ //right border
                elist[i*size+j].push_back((i-1)*size + j); blackend.push_back(node);
                elist[i*size+j].push_back(i*size + j-1);
                elist[i*size+j].push_back( (i+1)*size + j-1 );			        
                elist[i*size+j].push_back( (i+1)*size + j );
            } else if(node > (size*(size-1)) && node < (size*size-1)){ //bottom border
                elist[i*size+j].push_back((i-1)*size + j); whiteend.push_back(node);
                elist[i*size+j].push_back( (i-1)*size + j+1);
                elist[i*size+j].push_back(i*size + j+1); 
            } else{ //internal node connectivity
                elist[i*size+j].push_back( (i-1)*size + j ); //top left
                elist[i*size+j].push_back( (i-1)*size + j+1); //top right
                elist[i*size+j].push_back(i*size + j-1); //left
                elist[i*size+j].push_back(i*size + j+1);//right
                elist[i*size+j].push_back( (i+1)*size + j-1 );//bottom left
                elist[i*size+j].push_back( (i+1)*size + j );//bottom right
            }
        }
    }
}
 
//Breadth First Search check if there is a connection between 2 nodes
bool Graph::checkwin(int s, int d, int size, int color){

    //Base case s = source, d = destination
    if (s == d)
        return true;
 
    //Mark vertices as not visited
    bool *visited = new bool[vert];
    for (int i = 0; i < vert; i++)
        visited[i] = false;
 
    //Create a queue for BFS
    list<int> queue;
 
    //Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    //Use value to get all adjacent vertices of a vertex
    list<int>::iterator i;
 
    while (!queue.empty()){
        //Dequeue a vertex from queue
        s = queue.front();
        queue.pop_front();
 
        //Get all adjacent vertices of the dequeued vertex s, if adjacent has not been visited,
        //then mark it visited and enqueue it
        for (i = elist[s].begin(); i != elist[s].end(); i++){
            //If this adjacent node is the destination node, return true
            if (*i == d && array[*i/size][*i%size] == color)
                return true;
 
            //If not continue BFS
            if (!visited[*i] && array[*i/size][*i%size] == color){
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    return false;
}

//Breadth First Search check if there is a connection between 2 nodes
bool Graph::testwin(int s, int d, int size, int color){

    //Base case s = source, d = destination
    if (s == d)
        return true;
 
    //Mark vertices as not visited
    bool *visited = new bool[vert];
    for (int i = 0; i < vert; i++)
        visited[i] = false;
 
    //Create a queue for BFS
    list<int> queue;
 
    //Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    //Use value to get all adjacent vertices of a vertex
    list<int>::iterator i;
 
    while (!queue.empty()){
        //Dequeue a vertex from queue
        s = queue.front();
        queue.pop_front();
 
        //Get all adjacent vertices of the dequeued vertex s, if adjacent has not been visited
        //then mark it visited and enqueue it
        for (i = elist[s].begin(); i != elist[s].end(); i++){
            //If this adjacent node is the destination node, return true
            if (*i == d && board[*i/size][*i%size] == color)
                return true;
 
            //If not continue BFS
            if (!visited[*i] && board[*i/size][*i%size] == color){
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    return false;
}

//print the board each time player and AI make moves
void Graph::print_board(int size){
    int count=0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(array[i][j] == EMPTY) { cout << "* "; } 
            else if(array[i][j] == WHITE) { cout << "W "; } 
            else { cout << "B "; }
        }
        cout << endl; 
        count++; 
        for(int i = 0; i < count; i++)  
            cout << " "; 
    }
    cout << endl;
}

int main() {
    bool win = false, blackwon = false; 
	double simu = 500, blackcounter = 0.0, whitecounter = 0.0;
    double prob_b = 0.0, prob_w = 0.0, maxprob = 0.0, prob = 0.0;
	int swaps = -1, size = 0, turn = 0, flag = 0, flag2 = 0;
    int color = -1, random = -1, blacknode = -1; 
    int a = -1, b = -1, x = -1, y = -1, aix = -1, aiy = -1;   
    srand(time(0)); 
 
    //take in size of board and make the connections
    cout<<"Please enter the size of the board: 11 or 13: ";
    cin>>size;
    Graph g(size*size);
    g.addEdge(size);
  
    //Set the boards to empty
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            g.array[i][j] = EMPTY;
            g.board[i][j] = EMPTY;
        }
    }

    //WHITE TURN: WIN IF CONNECT TOP AND BOTTOM
    while(flag == 0) { //if type in wrong coordinates have to type in again
        cout << "WHITE TURN: ";
        cin >> a; cin >> b;
        if(a<size && a>-1 && b<size && b>-1 && g.array[a][b] == 2){
            g.array[a][b] = WHITE; flag = 1; turn++;
        }
    }
    flag = 0; //flag help prompt you input right answer
    g.print_board(size);

    //pi rule section
    if(turn == 1) { //if want to swap with white pick 1
        cout << "PIE RULE: BLACK PLAYER SWAP OR NO" << endl; 
        for(int i = size/2-2; i < size/2+3; i++) { //if player pick values in the middle of board AI swap
            for(int j = size/2-2; j < size/2+3; j++) {
                if(g.array[i][j] == WHITE) {
                    swaps = 1; break;
                }
            }
        }
    }
    g.print_board(size);

    if(swaps == 1) { //IF swaps, WHITE PLAYER BECOMES BLACK PLAYER
        g.array[a][b] = BLACK;  //change white to black
        g.blackset.push_back(a*size+b); cout << "BLACK SWAPPED" << endl; 
        g.print_board(size); g.picked.push_back(a*size+b);
    } else { 
	    g.whiteset.push_back(a*size+b); 
		g.picked.push_back(a*size+b); 
	}
   
    while(flag == 0 && swaps == 1) { //white player turn now
        cout << "WHITE TURN: "; swaps = 2;
        cin >> x; cin >> y;
        if(x<size && x>-1 && y<size && y>-1 && g.array[x][y] == 2) {
            g.array[x][y] = WHITE; flag = 1; g.whiteset.push_back(x*size+y);
            g.picked.push_back(x*size+y);
        }
    }
    flag = 0;
    g.print_board(size);
    
    while(win != true) {
        cout << "BLACK TURN: " << endl; //BLACK WIN IF CONNECT LEFT AND RIGHT BORDERS

        //Start Monte Carlo method
        //pick simulated node as black
        for(int p = 0; p < size*size; p++) {
            if(g.array[p/size][p%size] == EMPTY) {
                g.board[p/size][p%size] = BLACK;
            }

            //fill simulated board with picked values
            for(int i = 0; i < g.picked.size(); i++) {
                aix = g.picked[i]/size; aiy = g.picked[i]%size;
                if(g.array[aix][aiy] == WHITE && g.board[aix][aiy] == EMPTY) {
                    g.board[aix][aiy] = WHITE;
                } else if(g.array[aix][aiy] == BLACK && g.board[aix][aiy] == EMPTY){
                    g.board[aix][aiy] = BLACK;
                }
            }

            //simulate board 500 times
            for(int co = 0; co < simu; co++){
                //fill in random black and white for simulated board every simulation
                for(int i = 0; i < size; i++) {
                    for(int j = 0; j < size; j++) {
                        if(g.board[i][j] == EMPTY) {
                            random = rand()%10;
                            if(random <= 4) { g.board[i][j] = BLACK; }
                            else if(random > 4) { g.board[i][j] = WHITE; }
                        }
                    }
                }

                //go through simulated board and check win for black and white player
                color = BLACK;
                for(int i = 0; i < g.blackstart.size(); i++) {
                    for(int j = 0; j < g.blackend.size(); j++) {
                        if(g.testwin(g.blackstart[i],g.blackend[j],size,color)){
                            blackcounter++; break; }
                    }
                }

                color = WHITE;
                for(int i = 0; i < g.whitestart.size(); i++) {
                    for(int j = 0; j < g.whiteend.size(); j++) {
                        if(g.testwin(g.blackstart[i],g.blackend[j],size,color)){ 
					        whitecounter++; break; }
                    }
                }

                //clean random picks every round
                for(int i = 0; i < size; i++) {
                    for(int j = 0; j < size; j++) {
                        if(g.array[i][j] == EMPTY && (i*size+j != p)) {
                            g.board[i][j] = EMPTY;
                        }
                    }
                }
            }

            //calculate and compare probability of white and black wins
            prob_w = (whitecounter/simu)*100;
            prob_b = (blackcounter/simu)*100;
            blackcounter = 0.0; whitecounter = 0.0;

            //pick the best probability that black should make a move to
            if(prob_w > prob_b && g.array[p/size][p%size] == EMPTY) { prob = prob_w; }
            else if(prob_w <= prob_b && g.array[p/size][p%size] == EMPTY) { prob = prob_b; }

            //if probability of the node checked is higher than max probability, make it the max and keep the node
            if(prob > maxprob) {
                maxprob = prob;
                blacknode = p;
            }
        }

        if(g.array[blacknode/size][blacknode%size] != EMPTY) {
            for(int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    if(g.array[i][j] == EMPTY) {
                        blacknode = i*size+j; break;
                    }
                }
            }
        }
        //AI puts in the node where it has the highest probability of winning
        g.array[blacknode/size][blacknode%size] = BLACK; g.blackset.push_back(blacknode); g.picked.push_back(blacknode);
        flag = 0; g.print_board(size); maxprob = 0.0;

        //check if have at least one black node picked on left or right side
        for(int i = 0; i < g.blackset.size(); i++) {
            if(g.blackset[i]%size == 0 || g.blackset[i]%size == (size-1) || 
			  g.blackset[i] == 0 || g.blackset[i] == size-1 || 
			  g.blackset[i] == (size*(size-1)) || g.blackset[i] == (size*size-1)) {
                flag2 = 1; color = BLACK;
                break;
            }
        }

        //test for black win by looking for connection between left and right borders
        if(flag2 == 1 && g.blackset.size() >= size) {
            for(int h = 0; h < g.blackset.size(); h++) {
                if(g.blackset[h] == 0 || g.blackset[h] == size*(size-1) || g.blackset[h]%size == 0) {
                    for(int i = 0; i < g.blackset.size(); i++) {
                        if(g.blackset[i] == size-1 || g.blackset[i] == size*size-1 || g.blackset[i]%size  == (size-1)) {
                            if(g.checkwin(g.blackset[h], g.blackset[i], size, color)) {
                                cout << "BLACK WIN" << endl; win = true; blackwon = true;
                                break;  
                            }
                        }
                    }
                }
            }
        }
        flag2 = 0;

        while(flag == 0 && blackwon == false) {//WHITE PLAYER move
            cout << "WHITE TURN: ";
            cin >> x; cin >> y; //input x and y coordinates, if wrong try again
            if(x<size && x>-1 && y<size && y>-1 && g.array[x][y] == EMPTY) {
                g.array[x][y] = WHITE; flag = 1; g.whiteset.push_back(x*size+y);
                g.picked.push_back(x*size+y);
            }
        }

        flag = 0; 
        g.print_board(size);//print board 

        //check if what you picked have values on top or bottom border
        for(int i = 0; i < g.whiteset.size(); i++) {
            if((g.whiteset[i] >= 0 && g.whiteset[i] < size) || 
               (g.whiteset[i] >= size*(size-1) && g.whiteset[i] <(size*size))) {
                flag2 = 1; color = WHITE;
                break; 
            }
        }

        //start the check win-lose condition for white, check for connection between top and bottom borders
        if(flag2 == 1 && g.whiteset.size() >= size) {
            for(int i = 0; i < size; i++) {
                for(int j = size*(size-1); j < size*size; j++) {
                    if(g.array[i/size][i%size] == WHITE && g.array[j/size][j%size] == WHITE) {
                        if(g.checkwin(i,j,size,color)) { cout << "WHITE WIN" << endl;
                            win = true; break;
                        }
                    }
                }
            }
        }
        flag2 = 0;
    }
}
