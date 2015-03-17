/**
* hex.cpp
*
* Files:   hex.cpp   README.txt
* Partner: N/A   (I worked alone)
* What I've learned can be found in the readme
*
*    *********                                                          *********
*    ***** If program terminates prematurely, see comment at bottom of code *****
*    *********                                                          *********
*/

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cstring>
#include <queue>
#include <deque>
#include <ctime>

using namespace std;

// Create an enum for possible board tiles
// Red team tries to span the board horizontally (x=0 -> x=10), blue vertically (y=0 -> y=10)
enum color{
    BLANK, RED, BLUE
};


// Create a point class for use in BFS and by the computer for determining its moves
class point{
    public:
        point(int a, int b){
            x = a;
            y = b;
            next = NULL;
        };

    public:
        int x;
        int y;
        point* next;
};



// Class for a list of point pointers
class pList{
    public:
        pList(){
            head = NULL;
            tail = NULL;
            length = 0;
        }

        ~pList(){
            point* curr = head;
            point* temp;
            while(curr != NULL){
                temp = curr;
                curr = curr->next;
                delete(temp);
            }
            head = NULL;
            tail = NULL;
        }

        void addNode(int i, int j){
            length ++;
            point* p = new point(i,j);
            if(tail == NULL){
                head = tail = p;
            } else {
                tail->next = p;
                tail = p;
            }
        }

    public:
        point* head;
        point* tail;
        int length;
};




//// For debug purposes:
// Print the values in the array in a rhombus
void printArray(int** A, int s){
    cout << endl << endl;
    ////// The board
    for(int j = 0; j < s; j++){
        // Insert the appropriate number of spaces before each new row, and label the first points
        for(int spaces = 0; spaces < j; spaces++) cout << "  ";
        // Print the value of each index in the array
        for(int i = 0; i < s; i++){
            if(A[i][j] != 0){
                if(A[i][j] < 10)
                    cout << "  " << A[i][j] << " ";
                else
                    cout << "  " << A[i][j];
            }
            else
                cout << "  . ";
        }
        cout << endl << endl;
    }
    cout << endl;
};




void addPriority(color** board, int** priorityArray, int a, int b, int s){
    if(board[a][b] == RED){

        // Priority is left to right
        for(int j = b; j <= a+b ; j++){
            if(j >= s) break;
            for(int i = 0; i <= a - (j-b); i++){
                // Keep the iteration within the bounds of the array
                if(board[i][j] == BLANK){
                    priorityArray[i][j] ++;
                }
            }
        }
        for(int j = b; j > b - (s-a) ; j--){
            if(j < 0) break;
            for(int i = a + (b-j); i < s; i++){
                // Keep the iteration within the bounds of the array
                if(board[i][j] == BLANK){
                    priorityArray[i][j] ++;
                }
            }
        }

    } else {

        // Priority is top to bottom
        for(int j = b-1; j >= 0; j--){
            for(int i = a; i <= (b-j) + a; i++){
                // Keep the iteration within the bounds of the array
                if(i >= s) break;
                if(board[i][j] == BLANK){
                    priorityArray[i][j] ++;
                }
            }
        }
        for(int j = b+1; j < s; j++){
            for(int i = a - (j-b); i <= a; i++){
                // Keep the iteration within the bounds of the array
                if(i < 0) continue;
                if(board[i][j] == BLANK){
                    priorityArray[i][j] ++;
                }
            }
        }

    }

}



// Returns a list of points of maximum priority
pList* getMax(int** A, int s){
    pList* L = new pList();
    // Start the maximum priority at 0
    int max = 0;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++){
            if(A[i][j] > max)
                max = A[i][j];
        }
    }
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++){
            if(A[i][j] == max)
                L->addNode(i,j);
        }
    }
    return(L);
}




// Constrains the maximum priority value (to help the strategy)
void constrainMax(int** A, int s){
    int max = 0;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++){
            if(A[i][j] > max)
                max = A[i][j];
        }
    }
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++){
            if(A[i][j] > max-1)
                A[i][j] = max-1;
        }
    }
}



// Return whether or not there is a point of the specified color at that position
bool checkPos(color** board, color compColor, int x, int y, int s){
    bool colorThere = true;
    if(x >= 0 && x < s && y >= 0 && y < s)
        colorThere = (board[x][y] == compColor);
    return(colorThere);
}


// Determine through a weighted algorithm where the optimal move is
point* priorityCheck(color** board, int s, color compColor){
    // Create an array for checking the priority of each space in the board
    int** priorityArray = new int*[s];
    for(int i = 0; i < s; i++){
        priorityArray[i] = new int[s];
        for(int j = 0; j < s; j++){
            priorityArray[i][j] = 0;
        }
    }
    // Iterate through the board, looking for pieces
    for(int j = 0; j < s; j++){
        for(int i = 0; i < s; i++){
            if(board[i][j] != BLANK)
                addPriority(board, priorityArray, i, j, s);
        }
    }

    point* curr;

    // Re-roll the following if the computer makes a poor decision for placement
    bool repeat = true;
    do{

//// For debugging purposes, print the priority array (looks interesting though)
//printArray(priorityArray,s);


        pList* maxPriority = getMax(priorityArray, s);
        int R = rand() % maxPriority->length;
        curr = maxPriority->head;
        for(int i = 0; i < R; i++){
            curr = curr->next;
        }
        // Check if the computer tries to place a piece in a poor adjacent position
        if(compColor == BLUE){

            bool left, right, up, down;
            // Check for same color pieces adjacent
            left = checkPos(board, BLUE, curr->x - 1, curr->y, s);
            right = checkPos(board, BLUE, curr->x + 1, curr->y, s);
            if( !left && !right )
                repeat = false;
            else {
                if(left && !right){
                    up = checkPos(board, BLUE, curr->x, curr->y - 1, s);
                    down = checkPos(board, BLUE, curr->x - 1, curr->y + 1, s);
                } else
                if(right && !left){
                    up = checkPos(board, BLUE, curr->x + 1, curr->y - 1, s);
                    down = checkPos(board, BLUE, curr->x, curr->y + 1, s);
                } else repeat = false;
                // Check for poor position
                if( !up || !down) repeat = false;
            }

            // Check for opponent pieces adjacent
            left = checkPos(board, RED, curr->x - 1, curr->y, s);
            right = checkPos(board, RED, curr->x + 1, curr->y, s);
            if( !left && !right )
                repeat = false;
            else {
                if(left && !right){
                    up = checkPos(board, RED, curr->x + 1, curr->y - 1, s);
                    down = checkPos(board, RED, curr->x - 1, curr->y, s);
                } else
                if(right && !left){
                    up = checkPos(board, RED, curr->x + 1, curr->y, s);
                    down = checkPos(board, RED, curr->x - 1, curr->y + 1, s);
                } else repeat = false;
                // Check for poor position
                if( !up || !down) repeat = false;
            }

        } else {

            bool left, right, up, down;
            // Check for same color pieces adjacent
            left = checkPos(board, RED, curr->x, curr->y - 1, s);
            right = checkPos(board, RED, curr->x, curr->y + 1, s);
            if(!left && !right)
                repeat = false;
            else {
                if(left && !right){
                    up = checkPos(board, RED, curr->x + 1, curr->y - 1, s);
                    down = checkPos(board, RED, curr->x - 1, curr->y, s);
                } else
                if(right && !left){
                    up = checkPos(board, RED, curr->x + 1, curr->y, s);
                    down = checkPos(board, RED, curr->x - 1, curr->y + 1, s);
                } else repeat = false;
                // Check for poor position
                if( !up || !down) repeat = false;
            }

            // Check for opponent pieces adjacent
            left = checkPos(board, BLUE, curr->x - 1, curr->y, s);
            right = checkPos(board, BLUE, curr->x + 1, curr->y, s);
            if( !left && !right )
                repeat = false;
            else {
                if(left && !right){
                    up = checkPos(board, BLUE, curr->x, curr->y - 1, s);
                    down = checkPos(board, BLUE, curr->x - 1, curr->y + 1, s);
                } else
                if(right && !left){
                    up = checkPos(board, BLUE, curr->x + 1, curr->y - 1, s);
                    down = checkPos(board, BLUE, curr->x, curr->y + 1, s);
                } else repeat = false;
                // Check for poor position
                if( !up || !down) repeat = false;
            }

        }
        constrainMax(priorityArray, s);
    } while(repeat);

    for(int i = 0; i < s; i++){
        delete[] priorityArray[i];
    }
    delete[] priorityArray;

    return(curr);

};




// Add the point to the Queue if it has not been visited already
void queueAdd(queue<point*> *Q, bool** visited, point* p){
    if( !visited[p->x][p->y] ){
        Q->push(p);
        visited[p->x][p->y] = true;
    } else{
        // If the point has been visited, delete the temporary point reference
        delete(p);
    }
};



// Add all of the neighbors of the front point on the queue, and remove it from the queue
void addNeighbors(queue<point*> *Q, bool** v, color** board, color c, int s){
    point* p = Q->front();
    Q->pop();
    // The following variables account for whether a point is on the edge of the rhombus
    bool xBig, xSmall, yBig, ySmall;
    xBig = (p->x > 0);
    xSmall = (p->x < s-1);
    yBig = (p->y > 0);
    ySmall = (p->y < s-1);

    point* temp;

    // Add the non-visited neighbor pieces of the current piece to the queue
    // These outer if statements deal with edge-of-rhombus points, which have fewer neighbors
    if(xBig){
        // Add the left
        temp = new point(p->x - 1, p->y);
        if(board[temp->x][temp->y] == c)
            queueAdd(Q, v, temp);
        else delete(temp);
        if(ySmall){
            // Add the lower left
            temp = new point(p->x - 1, p->y + 1);
            if(board[temp->x][temp->y] == c)
                queueAdd(Q, v, temp);
            else delete(temp);
        }
    }
    if(yBig){
        // Add the upper left
        temp = new point(p->x, p->y - 1);
        if(board[temp->x][temp->y] == c)
            queueAdd(Q,v,temp);
        else delete(temp);
        if(xSmall){
            // Add the upper right
            temp = new point(p->x + 1, p->y - 1);
            if(board[temp->x][temp->y] == c)
                queueAdd(Q,v,temp);
            else delete(temp);
        }
    }
    if(xSmall){
        // Add the right
        temp = new point(p->x + 1, p->y);
        if(board[temp->x][temp->y] == c)
            queueAdd(Q,v,temp);
        else delete(temp);
    }
    if(ySmall){
        // Add the lower right
        temp = new point(p->x, p->y + 1);
        if(board[temp->x][temp->y] == c)
            queueAdd(Q,v,temp);
        else delete(temp);
    }

    // After the point has been popped from the queue and its neighbors added, delete it
    delete(p);
};





// Print the board, displayed as a rhombus
void printBoard(color** board, int s){
    ////// Above the board
    cout << endl << endl << "   ";
    for(int i = 0; i < s; i++){
        if(i < 10)
            cout << i << " ";
        else
            // Print every even number greater than 10 above the board for easier reading
            if(i % 2 == 0)
            cout << i << "  ";
    }
    cout << endl;
    ////// The board
    for(int j = 0; j < s; j++){
        // Insert the appropriate number of spaces before each new row, and label the first points
        for(int spaces = 0; spaces < j; spaces++) cout << " ";
        if(j < 10)
            cout << j << "   ";
        else
            cout << j << "  ";

        // Print the appropriate symbol representing the color of each point
        for(int i = 0; i < s; i++){
            if(board[i][j] == BLANK) cout << ". ";
            if(board[i][j] == RED) cout << "o ";
            if(board[i][j] == BLUE) cout << "x ";
        }
        cout << " " << j << endl;
    }

    ////// Below the board
    // Initial spaces offset
    int offset = s + 4;
    for(int i = 0; i < offset; i++)
        cout << " ";
    // Number labels
    for(int i = 0; i < s; i++){
        if(i < 10)
            cout << i << " ";
        else
            // Print every odd number greater than 10 below the board for easier reading
            if(i % 2 == 1)
            cout << " " << i << " ";
    }

    cout << endl;
};


// Function performs BFS on the board to see if a path crosses the board for the given color
bool hasWon(color** board, color c, int s){
    bool winner = false;

    // Make a Queue for BFS
    queue<point*> myQueue;
    queue<point*> *Q = &myQueue;
    point* temp;

    // Create a boolean array to represent which points were visited already
    bool** visited = new bool*[s];
    for(int i = 0; i < s; i++){
        visited[i] = new bool[s];
        for(int j = 0; j < s; j++)
            visited[i][j] = false;
    }

    if(c == RED){
        // Run BFS for Red, with sources starting at (0,0), going to (0,10)
        for(int j = 0; j < s; j++){
            if(board[0][j] != RED) continue;
            temp = new point(0,j);
            Q->push(temp);
            visited[0][j] = true;
            while( !Q->empty() ){
                if( (Q->front())->x == s - 1 ){
                    winner = true;
                    break;
                }
                addNeighbors(Q, visited, board, c, s);
            }
            if(winner) break;
        }
    } else {
        // Run BFS for Blue, with sources starting at (0,0), going to (10,0)
        for(int i = 0; i < s; i++){
            if(board[i][0] != BLUE) continue;
            temp = new point(i,0);
            Q->push(temp);
            visited[i][0] = true;
            while( !Q->empty() ){
                if( (Q->front())->y == s - 1 ){
                    winner = true;
                    break;
                }
                addNeighbors(Q, visited, board, c, s);
            }
            if(winner) break;
        }
    }

    for(int i = 0; i < s; i++){
        delete[] visited[i];
    }
    delete[] visited;

    while( !(Q->empty()) ){
        point* temp = Q->front();
        Q->pop();
        delete(temp);
    }

    return(winner);
};




point* compMove(color** board, point* previous, color compColor, int s){
    delete(previous);

    previous = priorityCheck(board, s, compColor);

    board[previous->x][previous->y] = compColor;
    return(previous);
}


// Get the player's move from standard input, and add it to the board
void getMove(color** board, color playerColor, int s){
    // Print the board first
    printBoard(board, s);

    bool validMove = false;
    string a, b;
    int x = -1;
    int y = -1;
    do{
        cout << endl << "Input move: ";
        cin >> a >> b;
        if( !(istringstream(a) >> x && istringstream(b) >> y) ){
            cout << "Invalid input." << endl;
            continue;
        }
        if(x >= 0 && y >= 0 && x < s && y < s){
            if(board[x][y] == BLANK)
                validMove = true;
            else {
                cout << "Point already occupied." << endl << endl;
                x = -1;
                y = -1;
            }
        } else {
            cout << "Point must be on the board." << endl << endl;
            x = -1;
            y = -1;
        }
    } while( !validMove );

    board[x][y] = playerColor;
};


// Gets the player's first move, and returns the position of that move for later use
point* getFirstMove(color** board, int s){
    cout << endl << "Your goal is to make a 'horizontal' path of o's between the left and right sides" << endl;
    cout << "The board's directions are as follows: -x-, \\y\\." << endl;
    cout << "Input moves in the following format (without quotes): \"x y\"" << endl;
    getMove(board, RED, s);
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++){
            if(board[i][j] == RED){
                point* temp = new point(i, j);
                return(temp);
            }
        }
    }
    // This should never occur
    cout << "Error: First piece was never placed." << endl;
    return(NULL);
};


// Main method: gets the size of the board and initiates the first turn and the main game loop
int main(int argc, char** argv){
    // Seed the random function
    srand(time(NULL));

    // Get the size of the board
    string input;
    int size = -1;
    do{
        cout << "Insert board size: ";
        cin >> input;
        if( !(istringstream(input) >> size) ){
            cout << "Invalid character." << endl << endl;
            continue;
        }
        // Restrict the board to arbitrary limits
        if(size < 7 || size > 21)
            cout << endl << "Board size must be between 7 and 21." << endl << endl;
    } while(size < 7 || size > 21);


    // Set up the board as a 2D array of colors
    color** board = new color*[size]();
    for(int i = 0; i < size; i++){
        board[i] = new color[size]();
        for(int j = 0; j < size; j++){
            board[i][j] = BLANK;
        }
    }

    // Player starts out as Red (goal: horizontal connection)
    color playerColor = RED;
    color compColor = BLUE;
    point* temp = getFirstMove(board, size);

    //////
    ////// Implement the pie rule so that the computer will swap for the player if the player chooses an optimal point
    //////
    // Computer will swap with the player if the player chooses a move on or next to the shortest diagonal
    point* compPrevious = NULL;
    int dist = temp->x + temp->y + 1;
    if(dist >= size-1 && dist <= size+1) {
        cout << endl << "The computer has chosen to swap places with you." << endl;
        cout << "Your goal is now to make a 'vertical' path of x's between the top and bottom." << endl;
        cout << endl << "Please place your new first piece." << endl;
        playerColor = BLUE;
        compColor = RED;
        compPrevious = temp;
        getMove(board, playerColor, size);
    } else delete(temp);

    //////
    ////// Main game loop
    //////
    // Run the main game loop until someone wins
    while(true){
        compPrevious = compMove(board, compPrevious, compColor, size);
        cout << "Computer's move: " << compPrevious->x << " " << compPrevious->y << endl;

        // Check if the computer has won
        if(hasWon(board, compColor, size)){
            cout << endl << "----- You lost. -----" << endl;
            break;
        }
        getMove(board, playerColor, size);
        // Check if the player has won
        if(hasWon(board, playerColor, size)){
            cout << endl << endl << "----- You win! -----";
            break;
        }
    }

    // After the game ends, show the board
    printBoard(board, size);
    cout << endl << "---- Game over. ----" << endl;

    // Free up memory for the board and previous piece
    delete(compPrevious);

    for(int i = 0; i < size; i++)
        delete[] board[i];
    delete[] board;


///////////////////////////////////////////////////////////////////////////////////////////////////
// If the terminal window closes immediately after the program finishes, un-comment the following:

    //system("PAUSE");

///////////////////////////////////////////////////////////////////////////////////////////////////


    return(0);
};
