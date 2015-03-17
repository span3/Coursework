#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
using namespace std;

/*
 * Monte Carlo AI Class
 */
class MCAI{
public:
	MCAI(Board *, bool);
	void doMoves();
	void getBestSpot();
	
private:
	//The local board that is going to be used
	Board *localBoard;
	//The count of starting moves to successful victories
	vector<vector<int> > moveCount;
	int startingX, startingY;
	bool currentPlayer;
};
