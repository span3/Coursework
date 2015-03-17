//#define C11
#define SIMSPERMOVE  1000
#ifdef C11
#include<thread>
#endif

#include<iostream>
#include<string>
#include<cstdlib>
#include<utility>
#include<algorithm>
#include<ctime>
#include "hex.h"
using namespace std;

Hex::Hex(int size)
{
	this->size = size;
	playedCount = 0;
	g = Graph(size);
}

void Hex::play()
{
	g.resetNodes();
	cout <<endl<< "Welcome to the Game of Hex!"<<endl<<endl<<
		"The Computer is WHITE and will start first"<< endl<<
		"You are BLACK and will play second"<<endl<<
		"After the first move, you will have the opportunity to switch colors"<<endl<<
		endl<<"Here is the starting board"<<endl;
	g.printOffset();
	
	cout << "Ready? (press enter): ";
	cin.clear();
	cin.ignore(1000, '\n');

	
	cout << "Computer's Move" <<endl;
	doCPUMoveMC(WHITE);
	playedCount++;
	
	g.printOffset();
	cout << "PIE RULE: Do you want to switch sides? (y/n): ";
	string pie;
	cin >> pie;
	cin.clear();
	cin.ignore(1000, '\n');
	bool pieRuleChosen = false;
	if(pie.compare("y") == 0)
	{
		pieRuleChosen = true;
	}
	
	
	if(pieRuleChosen)
	{
		cout << "You have elected to switch" <<endl
		<<"The Computer will go again, it is now BLACK"<<endl;
		playOnSwitched();
	}
	else
	{
		cout  << "You have not elected to switch"<<endl
		<<"It is now your turn"<<endl;
		playOn();
	}
}

//Player is BLACK
//Computer is WHITE
inline void Hex::playOn()
{
	int gameCounter = 1; //%2 == 1 is a BLACK move
	while(!g.sentinelPathComplete())
	{
		if(gameCounter % 2 == 1) //Black move
		{
			bool validMove = false;
			while(!validMove)
			{
				cout << "Please only enter integers, anything else will be interpreted as 0"<<endl;

				string moveX;
				cout<<"Please enter x coordinate of move: ";
				cin >> moveX;
				int xCoor = atoi(moveX.c_str());
	
				string moveY;
				cout<<"Please enter y coordinate of move: ";
				cin >> moveY;
				int yCoor = atoi(moveY.c_str());
				if(xCoor >= 0 && xCoor < size && yCoor >=0 && yCoor < size && g.isColoringValid(xCoor,yCoor))
				{
					cout<<"MOVE VALID" <<endl;
					validMove = true;
					g.setColor(xCoor,yCoor,BLACK);
				}
				else
				{
					cout << "MOVE INVALID"<<endl;
				}
				
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else //white move
		{
			//THREADING
			#ifdef C11
			thread t1(&Hex::doCPUMoveMC, this, WHITE);
			t1.join();
			#else 
			doCPUMoveMC(WHITE);
			#endif
			//THREADING
		}
		g.printOffset();
		playedCount++;
		gameCounter++;
	}
}

//Player is WHITE
//Computer is BLACK
inline void Hex::playOnSwitched()
{
	int gameCounter = 0; //%2 == 1 is a BLACK move
	while(!g.sentinelPathComplete())
	{
		if(gameCounter % 2 == 1) //Black move
		{
			bool validMove = false;
			while(!validMove)
			{
				cout << "Please only enter integers, anything else will be interpreted as 0"<<endl;

				string moveX;
				cout<<"Please enter x coordinate of move: ";
				cin >> moveX;
				int xCoor = atoi(moveX.c_str());
	
				string moveY;
				cout<<"Please enter y coordinate of move: ";
				cin >> moveY;
				int yCoor = atoi(moveY.c_str());
				if(xCoor >= 0 && xCoor < size && yCoor >=0 && yCoor < size && g.isColoringValid(xCoor,yCoor))
				{
					cout<<"MOVE VALID" <<endl;
					validMove = true;
					g.setColor(xCoor,yCoor,WHITE);
				}
				else
				{
					cout << "MOVE INVALID"<<endl;
				}
				
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else //white move
		{
			//THREADING
			#ifdef C11
			thread t1(&Hex::doCPUMoveMC, this, BLACK);
			t1.join();
			#else 
			doCPUMoveMC(BLACK);
			#endif
			//THREADING
		}
		
		g.printOffset();
		playedCount++;
		gameCounter++;
	}
}

//simple AI that prioritizes a line through the middle
void Hex::doCPUMove(Color col)
{
	//monteCarloSim(g, col);
	bool madeMove = false;
	if(col == WHITE)
	{
		if(g.isColoringValid(size/2, size/2))
		{
			madeMove = true;
			currentX = size/2;
			currentY = size/2;
			g.setColor(size/2,size/2, col);
		}
		else
		{
			while(!madeMove)
			{
				int x = (currentX + ((rand() % size/2) - size/4)) % size;
				int y = (currentY + ((rand() % 3 - 1))) % size;
				if(g.isColoringValid(x,y))
				{
					currentX = x;
					currentY = y;
					g.setColor(currentX,currentY,col);
					madeMove = true;
				}
			}
		}
	}
	else if(col == BLACK)
	{
		if(g.isColoringValid(size/2, size/2))
		{
			madeMove = true;
			currentX = size/2;
			currentY = size/2;
			g.setColor(size/2,size/2, col);
		}
		else
		{
			while(!madeMove)
			{
				int y = (currentY + ((rand() % size/2) - size/4)) % size;
				int x = (currentX + ((rand() % 3 - 1))) % size;
				if(g.isColoringValid(x,y))
				{
					currentX = x;
					currentY = y;
					g.setColor(currentX,currentY,col);
					madeMove = true;
				}
			}
		}
	}
}

inline void Hex::doCPUMoveMC(Color col)
{
	int numSims = SIMSPERMOVE;
	pair<int,int> move = monteCarloSim(g,numSims, col);
	g.setColor(move.first, move.second, col);
	cout<<"AI Move: ("<<move.first<<","<<move.second<<")"<<endl;
}

inline void Hex::winningPercentage(int numSims, vector<int> winTable)
{
	int cnt = 0;
	int zeros = 0;
	for(int i = 0; i < g.getNumNodes() - 4; i++)
	{
		cnt += winTable[i];
		if(winTable[i] == 0)
			zeros++;
	}
	double percentage = 100.0*(static_cast<double>(cnt) / static_cast<double>((g.getNumNodes() - zeros) * numSims));
	cout << "Your Winning % = " << 100  - percentage << endl;
}

//The graph that is passed in is the board
//Runs a bunch of sims using random number generators.
//Returns the x/y of the move with the highest winning percentage
inline pair<int,int> Hex::monteCarloSim(Graph inGraph, int numSims, Color col)
{	
	int t0 = time(NULL);
	vector<int> winTable(size*size, 0);
	
	#ifdef C11
	vector<thread> threads; //THREADING 
	#endif
	
	for(int i = 0; i < inGraph.getNumNodes() - 4; ++i) //for each unplayed node
	{
		if(inGraph.getNodeAt(i).getPlayer() == NOCOLOR)
		{
			Graph movedOnGraph = inGraph;
			movedOnGraph.setColor(i%size, i/size, col);
			//now run simulations on this 
			
			#ifndef C11
			winTable[i] = runSim(movedOnGraph, numSims, col, winTable);
			#else
			//THREADING
			threads.push_back(thread(&Hex::runSim, this, movedOnGraph, numSims, col, ref(winTable), i));
			#endif
			
		}
	}
	//THREADING
	#ifdef C11
	for(vector<thread>::iterator i = threads.begin(); i != threads.end(); ++i)
	{
		(*i).join();
	}
	#endif
	//THREADING
	
	
	for(int p = 0; p < winTable.size(); ++p)
	{
		cout << winTable[p] << " ";
	}
	cout << endl << "Time Elapsed: " << time(NULL)-t0<<" sec"<<endl;
	int max = find_max(winTable);
	winningPercentage(numSims, winTable);
	//cout << max<< endl;
	pair<int,int> p(max%size, max/size);
	return p;
}

//returns the number of wins in the sim
inline int Hex::runSim(Graph simG, int sims, Color col, vector<int> &table, int tableIndex)
{
	int winCount = 0;
	for(int c = 0; c < sims; ++c)
	{
		Graph singleSimGraph = simG;
		int unPlayedCount = singleSimGraph.getNumNodes() - playedCount; //0;
		/*for(int i = 0; i < singleSimGraph.getNumNodes() - 4; i++)
		{
			if(singleSimGraph.getNodeAt(i).getPlayer() == NOCOLOR)
			{
				unPlayedCount++;
			}
		}*/
	
		vector<Color> colorList(unPlayedCount/2, WHITE);
		//vector<Color> blackPart(unPlayedCount/2, BLACK);
		for(int i = 0; i < unPlayedCount/2; ++i)
		{
			colorList.push_back(BLACK);
		}
		
		
		//colorList.insert(colorList.end(), blackPart.begin(), blackPart.end());
		random_shuffle(colorList.begin(), colorList.end());
	
		int i = 0,j = 0; // i is an index to the total graph
		//j is an index to the shuffled colorList
		while(i < singleSimGraph.getNumNodes() && j < unPlayedCount)
		{
			if(singleSimGraph.getNodeAt(i).getPlayer() == NOCOLOR)
			{
				singleSimGraph.setColor(i%size, i/size, colorList[j]);
				++j;
			}
			++i;
		}
		
		//singleSimGraph.resetNodes();
		if(singleSimGraph.sentinelPathCompleteWithColor() == col)
		{
			++winCount;
		}			
	}
	// THREADING STUFF
	#ifdef C11
	table[tableIndex] = winCount; //USED FOR THREADING
	#endif
	//END THREADING STUFF
	return winCount;
}

inline int Hex::find_max(vector<int> vec)
{
	int maxIndex = 0;
	for(int i = 0; i < vec.size(); ++i)
	{
		if(vec[i] > vec[maxIndex])
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}






