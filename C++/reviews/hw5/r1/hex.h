#include "graph.h"
#include<utility>
class Hex
{
	public:
		Hex(int size);
		void play();
	private:
		int size;
		Graph g;
		int playedCount;
		
		//Computer player stuffs
		int currentX;
		int currentY;
		void doCPUMove(Color c);
		void doCPUMoveMC(Color c);
		void playOn();
		void playOnSwitched();
		pair<int,int> monteCarloSim(Graph tempG, int numSims, Color col);
		int runSim(Graph simG, int sims, Color col, vector<int> &table, int tableIndex = 0);
		int find_max(vector<int> vec);
		void winningPercentage(int numSims, vector<int> winTable);
};