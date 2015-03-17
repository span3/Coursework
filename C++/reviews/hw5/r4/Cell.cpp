#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
#include "Cell.h"
using namespace std;

/*
 * A debug ability to print the contents of a cell
 */
void Cell::print(){
    cout << "Cell (" << spotX << "," << spotY << ")\n";
    cout << "Filled: " << filled << " Player One?" << playerOne << endl;
}

//returns the filled value true if cell is occupied
bool Cell::getFill(){return filled;}
//returns if playerOne is selected or not
bool Cell::getPlayer(){return playerOne;}
//returns x value
int Cell::getX(){return spotX;}
//returns y value
int Cell::getY(){return spotY;}

/*
 * @param sets the value of that cell to the value passed in
 */
void Cell::setFill(bool value, bool playerOne){
    this->filled = value;
    this->playerOne = playerOne;
}

/*
 * constructor
 * @param x: x cord
 * @param y: y cord
 */
Cell::Cell(int x, int y){
    this->spotX = x;
    this->spotY = y;
    this->filled = false;
    //Nil is inputted so that it is not pointing to null but also not pointing to random memory
    this->connectTo = &Nil;
}
