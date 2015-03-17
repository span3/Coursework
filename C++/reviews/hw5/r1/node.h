#include "edge.h"

class Node
{
	public:
		Node();
		Node(int);
		Node(Color c){playedInHex = c;}
		bool operator>(const Node n) const;
		int getTempDist() const {return tempDist;}
		void setTDist(int n){tempDist = n;}
		bool getVisited(){return visited;}
		void setVisited(bool b){visited = b;}
		void append(Edge e);
		int getDeg(){return edgeList.size();}
		int getNodeAt(int index,int nodeNum);//gets the node # from the edge at the position that is not this number
		int getListSize(){return edgeList.size();}
		int getNodeIndexFromEdgeAt(int i, int currentNode);
		int getWeightFromEdgeAt(int i);
		void addToTempDist(int i, int j);
		Color getEdgeColor(int i){return edgeList[i].getC();}
		Edge getEdgeAt(int i){return edgeList[i];}
		friend ostream& operator<<(ostream& out, Node n);
		Color getPlayer(){return playedInHex;}
		void setPlayer(Color c){playedInHex = c;}
		void setEdgeColor(int index, Color c){edgeList[index].setC(c);}
		int getEdgeIndexFromList(int node);
	private:
		int tempDist; // used in dijkstras alg
		bool visited; //used to implement open set/closed set for dijkstras alg
		vector<Edge> edgeList; //list of edges this node is connected to
		Color playedInHex;
};
