#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
#include "Global.h"
#include "Cell.cpp"
#include "Board.cpp"
#include "MCAI.cpp"
using namespace std;

/*
 * Main
 */
int main(){
    //seed the random number generator for true random
    srand(time(0));
    //init board and AI
    /*int size = 11;
    cout << "Please specify a board size (between 5 and 11):\n";
    cin >> size;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        size = 11;
        cout << "DEFAULT SET TO 11\n";
    }
    if(size > 11 || size < 5){
        cout << "DEFAULT SET TO 11\n";
        size = 11;
    }*/
    Board board(_GLOBAL::SIZE);
    MCAI AItwo(&board, false);
    MCAI AIone(&board, true);
	
    //init important variables
    bool gameOver = false;
    int moveX = 0;
    int moveY = 0;
    bool playerOne = true;
    AItwo.doMoves();
    //Check if playerOne accepted first move
    if(_GLOBAL::playerOneMovedFirst)
        playerOne = false;
    //keep looping until the game is over
    while(!gameOver){
        cout << endl << endl;
        (playerOne)? cout << "Player One's Turn (X) - Left to Right\n":cout << "Player Two's Turn (O) - Top to Bottom\n";
        board.print();
        bool done = false;
        //keep looping until a valid move has been performed
        while(!done){
            if(!playerOne){
                AItwo.doMoves();
                playerOne = !playerOne;
                break;
            }else{
                //AIone.doMoves();
                //playerOne = !playerOne;
                //break;
            }
            //run player move
            cout << "Please enter an X value between 0 and " << _GLOBAL::SIZE-1 << ":\n";
            cin >> moveX;
            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "INCORRECT INPUT\n";
                continue;
            }
            cout << "Please enter an Y value between 0 and " << _GLOBAL::SIZE-1 << ":\n";
            cin >> moveY;
            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "INCORRECT INPUT\n";
                continue;
            }
            if(board.input(moveX, moveY, playerOne)){
                cout << "Moving to spot " << moveX << "," << moveY << endl;
                done = true;
                playerOne = !playerOne;
            }else{
                cout << "Can't move to spot " << moveX << "," << moveY << endl;
            }
        }
        //check if game is over
        if(board.getGameOver()){
            (!playerOne)?cout << "Player One Wins!\n":cout << "Player Two Wins!\n";
            board.print();
            break;
        }
    }
}
