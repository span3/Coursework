#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
#include "Board.h"
using namespace std;

//default constructor
//Pass in the size variable
Board::Board(int size){
    for(int i=0; i<size; i++){
        vector<Cell> tmp;
        for(int j=0; j<size; j++){
            Cell tmp2(i, j);
            tmp.push_back(tmp2);
        }
        boardArray.push_back(tmp);
    }
    this->size = size;
    this->gameOver = false;
}

//Returns if the game is over or not
bool Board::getGameOver(){return gameOver;}

//Checks if a spot is filled or not
bool Board::checkSpot(int x, int y){
    return (boardArray[y][x].getFill());
}

/*
 * This function prints out the entire board
 */
void Board::print(){
    for(int i=0; i<boardArray.size(); i++){
        for(int lineCount=0; lineCount<i; lineCount++)
            cout << " ";
        for(int j=0; j<boardArray[i].size(); j++){
            if(boardArray[i][j].getFill())
                (boardArray[i][j].getPlayer())?cout << "X ":cout << "O ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

/*
 * This function is called whenever there needs to be a move on the board
 * returns true if move was successful, false if it wasn't
 *
 * @param x: x cord of placed tile
 * @param y: y cord of placed tile
 * @playerOne: true if playerOne, false if playerTwo
 */
bool Board::input(int x, int y, bool playerOne){
    if(x < 0 || y < 0 || x > size-1 || y > size-1 || boardArray[y][x].getFill() == true)
        return false;

    boardArray[y][x].setFill(true, playerOne);
    checkGraph(x,y,playerOne);

    return true;
}

/*
 * This function is used to check if a player has won the game or not
 * It is called everytime a user places a tile. It does a DFS from the tile places to all
 * of the possible branches and where they lead.
 * @param x: x cord of placed tile
 * @param y: y cord of placed tile
 * @param playerOne: true if playerOne, false if playerTwo
 */
void Board::checkGraph(int x, int y, bool playerOne){
    vector<Cell> neighbors;
    vector<Cell> nodes;
    checked.clear();
    //Fills the checked vector of vectors
    //This is used to see which spots have been checked already and which havent
    //in order to not have a forever-loop
    for(int i=0; i<size; i++){
        vector<bool> tmpCheckedList;
        tmpCheckedList.resize(size,false);
        checked.push_back(tmpCheckedList);
    }
    //Init the top/bottom/left/right bools
    bool top = false, bottom = false, left = false, right = false;
    //initially check if the tile being placed is at the bottom, top, left, or right
    nodes = getNeighbors(x,y,playerOne);
        if(x == 0){
            left = true;
        }
        if(x == size-1){
            right = true;
        }
        if(y == 0){
            top = true;
        }
        if(y == size-1){
            bottom = true;
        }

    //keep going until all possible branches have been checked
    //The nodes list is a constant supply of connected neighbors branching from
    //the beginning node
    while(!nodes.empty()){
        Cell tmp = nodes.front();
        //again, check if the node we are checking is at the top, bottom, left, or right
        if(tmp.getY() == 0){
            left = true;
        }
        if(tmp.getY() == size-1){
            right = true;
        }
        if(tmp.getX() == 0){
            top = true;
        }
        if(tmp.getX() == size-1){
            bottom = true;
        }
        //add the neighbors to the list and pop the beginning cell
        neighbors = getNeighbors(tmp.getY(), tmp.getX(), playerOne);
        nodes.erase(nodes.begin());
        nodes.insert(nodes.end(), neighbors.begin(), neighbors.end());
    }
    //Check if the game is over
    if(top && bottom) gameOver = true;
    if(left && right) gameOver = true;
}

/*
 * Prints all the nodes and their status (filled, which player they are, their x/y cords)
 * @param n: a vector of cells to print out
 */
void Board::printNodes(vector<Cell> n){
    for(int i=0; i<n.size(); i++){
        n[i].print();
    }
}

/*
 * returns a vector of cells that include only neighbors that are for the current player selected
 * @param x: x cord
 * @param y: y cord
 * @param playerOne: true for playerOne, false for playerTwo
 */
vector<Cell> Board::getNeighbors(int x, int y, bool playerOne){
    vector<Cell> neighbors;
    checked[y][x] = true;

    //Node "Top Left"
    if(y>0){
        if(boardArray[y-1][x].getFill() && boardArray[y-1][x].getPlayer() == playerOne && checked[y-1][x] != true){
            neighbors.push_back(boardArray[y-1][x]);
            checked[y-1][x] = true;
        }
    }
    //Node "Top Right"
    if(x<(size-1) && y>0){
        if(boardArray[y-1][x+1].getFill() && boardArray[y-1][x+1].getPlayer() == playerOne && checked[y-1][x+1] != true){
            neighbors.push_back(boardArray[y-1][x+1]);
            checked[y-1][x+1] = true;
        }
    }
    //Node "Mid Right"
    if(x<(size-1)){
        if(boardArray[y][x+1].getFill() && boardArray[y][x+1].getPlayer() == playerOne && checked[y][x+1] != true){
            neighbors.push_back(boardArray[y][x+1]);
            checked[y][x+1] = true;
        }
    }
    //Node "Lower Right"
    if(y<(size-1)){
        if(boardArray[y+1][x].getFill() && boardArray[y+1][x].getPlayer() == playerOne && checked[y+1][x] != true){
            neighbors.push_back(boardArray[y+1][x]);
            checked[y+1][x] = true;
        }
    }
    //Node "Lower Left"
    if(y<(size-1) && x>0){
        if(boardArray[y+1][x-1].getFill() && boardArray[y+1][x-1].getPlayer() == playerOne && checked[y+1][x-1] != true){
            neighbors.push_back(boardArray[y+1][x-1]);
            checked[y+1][x-1] = true;
        }
    }
    //Node "Mid Left"
    if(x>0){
        if(boardArray[y][x-1].getFill() && boardArray[y][x-1].getPlayer() == playerOne && checked[y][x-1] != true){
            neighbors.push_back(boardArray[y][x-1]);
            checked[y][x-1] = true;
        }
    }
    return neighbors;
}
