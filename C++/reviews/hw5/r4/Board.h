#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
using namespace std;

//A forward declaration of the AI so that the Board class can friend it
class WeakAI;

/*
 * The board class handles all of the moves that the board can make
 * It also checks the win condition whenever a tile is placed
 */
class Board{
    public:
      Board(int);
      void print();
      bool input(int, int, bool);
      void checkGraph(int, int, bool);
      vector<Cell> getNeighbors(int,int,bool);
      void printNodes(vector<Cell>);
      bool getGameOver();
      bool checkSpot(int, int);
      inline int getBoardSize(){return size;}
      vector<vector<Cell> > *getBoardArray(){return &boardArray;}
      friend class WeakAI;

    private:
      vector< vector <Cell> > boardArray;
      int size;
      //a 2D array keeping track of what is in the graph
      vector< vector <bool> > inGraph;
      vector< vector <bool> > checked;
      bool gameOver;
};
