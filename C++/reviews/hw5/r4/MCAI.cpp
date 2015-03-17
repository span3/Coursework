#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
#include "MCAI.h"

/*
 * Constructor
 * @param b: passes in current board state
 */
MCAI::MCAI(Board *b, bool player){
    localBoard = b;
    currentPlayer = player;
}

/*
 * Randomly doing _GLOBAL::I_NUM variations of the board and 
 * records which start moves ended in success.
 */
void MCAI::doMoves(){
    //Clear all vectors for redoing everything
    moveCount.clear();
    vector<int> tempVec(_GLOBAL::SIZE, 0);
    //Initialize the variables we need
    moveCount.resize(_GLOBAL::SIZE, tempVec);
    int moveX = 0, moveY = 0;
    bool playerOne = false;
    //For loop for the iteration number
    for(int i=0; i<_GLOBAL::I_NUM; i++){
        //make a copy of the current board
        Board tempBoard = *localBoard;
        //a gameOver bool to find out when the tempboard is over
        bool gameOver = false;
        //bool to know when first move is
        bool firstMove = true;
        while(!gameOver){
            //keep looping until a valid move has been performed
            bool done = false;
            //keep generating random spots until we get an actual valid spot
            while(!done){
                moveX = rand()%_GLOBAL::SIZE;
                moveY = rand()%_GLOBAL::SIZE;
                if(tempBoard.input(moveX, moveY, playerOne)){
                    //cout << "Moving to spot " << moveX << "," << moveY << endl;
                    done = true;
                    playerOne = !playerOne;
                    if(firstMove){
                        //if its the first move, save the first move in case
                        //this is actually a winning spot
                        startingX = moveX;
                        startingY = moveY;
                        firstMove = false;
                    }
                }else{
                    //cout << "Can't move to spot " << moveX << "," << moveY << endl;
                }
            }
            //check if game is over for temp board
            if(tempBoard.getGameOver()){
                //if its the AI player, increment that spot in the 2d array
                if(!playerOne){
                    //Nothing
                }else{
                    moveCount[startingY][startingX]++;
                }
                break;
            }
        }
    }
    //Get the most winning spot
    getBestSpot();
    //If this is the first turn, execute pie rule
    if(_GLOBAL::firstTurn){
        _GLOBAL::firstTurn = false;
        int answer = 2;
        cout << "PIE RULE: The AI would like to move to " << startingX << "," << startingY << endl;
        cout << "Would you like to take that spot instead? (1 for yes, 0 for no)\n";
        while(answer = 2){
            cin >> answer;
            if(cin.fail()){
                cin.ignore(1000, '\n');
                cin.clear();
                answer = 2;
                continue;
            }else{
                break;
            }
        }
        if(answer == 1){
            localBoard->input(startingX, startingY, !currentPlayer);
            _GLOBAL::playerOneMovedFirst = true;
            return;
        }else{
            _GLOBAL::playerOneMovedFirst = false;
        }
    }
    //Do the move
    cout << "Doing move to: " << startingX << "," << startingY << endl;
    (localBoard->input(startingX, startingY, currentPlayer))?cout<<"Success\n":cout<<"NO!\n";
}

/*
 * This function goes through the whole list of spots that have been filled with
 * successful tries and finds the one with the most amounts of wins.
 * It then sets the startingX and startingY
 */
void MCAI::getBestSpot(){
    int bestX = 0, bestY = 0, bestCount = -1;
    //Loop to find the best one
    for(int i=0; i<_GLOBAL::SIZE; i++){
        for(int j=0; j<_GLOBAL::SIZE; j++){
            if(moveCount[i][j] > bestCount){
                bestCount = moveCount[i][j];
                startingX = j;
                startingY = i;
            }
        }
    }
}
