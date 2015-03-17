#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
using namespace std;

/*
 * Cell class keeps track of all of the relevant information regarding each cell on the board
 */
class Cell{
    public:
      //static vector< vector<Cell> > playerTwoList;

      Cell(int, int);
      void setFill(bool, bool);
      bool getFill();
      bool getPlayer();
      int getX();
      int getY();
      void input();
      void print();
      void printCellCords(){cout << spotY << "," << spotX << endl;}

    private:
      int spotX;
      int spotY;
      bool filled;
      bool playerOne;
      Cell *connectTo;
};
//Nil cell for default cells
Cell Nil(-1,-1);
