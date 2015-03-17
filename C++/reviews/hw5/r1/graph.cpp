#include<iostream>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<limits>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include<algorithm>
#include<set>
#include<stack>

#include "graph.h"
using namespace std;

std::ostream& operator<<(std::ostream& out, Color c)
{
	switch(c)
	{
		case 0: out << "Red";
				break;
		case 1: out << "Green";
				break;
		case 2: out << "Blue";
				break;
		case 3: out << "White";
				break;
		case 4: out << "Black";
				break;
		case 5: out << "NO COLOR";
				break;
	}
	return out;
}

Color getColor(std::string s)
{
	if(s.compare("r") == 0)
	{
		return RED;
	}
	else if(s.compare("g") == 0)
	{
		return GREEN;
	}
	else if(s.compare("b") == 0)
	{
		return BLUE;
	}
	else if(s.compare("w") == 0)
	{
		return WHITE;
	}
	else if(s.compare("bl") == 0)
	{
		return BLACK;
	}
	else return NOCOLOR;
}

//this is kind of weird, i can't remember why i had to do this, but it works
//This is used to compare edges.
bool operator<(Edge e1, Edge e2) 
{	
	if(e1.getW() != e2.getW())
	{
		return e1.getW() < e2.getW();
	}
	else
	{
		return true;
	}
}


Graph::Graph()
{
	
}

Graph::Graph(int size) //Used in hex
{
	this->numNodes = size*size;
	this->hexSize = size;
	nodes.resize(numNodes); //the board
	
	for(int i = 0; i < numNodes; i++)
	{
		Edge e1; //sides
		if(i%size!=0)
		{
			e1.set1(i);
			e1.set2(i-1);
			e1.setW(1);
			e1.setC(NOCOLOR);
			nodes[i].append(e1);
			nodes[i-1].append(e1);
			edges.push_back(e1);
		}
		Edge e2; //level above
		if(((i-(size-1)) >= 0) && ((i+1)%size!=0)) //testing the edge case
		{
			e2.set1(i);
			e2.set2(i-(size-1));
			e2.setW(1);
			e2.setC(NOCOLOR);
			nodes[i].append(e2);
			nodes[i-(size-1)].append(e2);
			edges.push_back(e2);
		}
		Edge e3; //level below
		if(i-size >= 0)
		{
			e3.set1(i);
			e3.set2(i-size);
			e3.setW(1);
			e3.setC(NOCOLOR);
			nodes[i].append(e3);
			nodes[i-size].append(e3);
			edges.push_back(e3);
		}
		
	}
	//Initializing Sentinel Nodes (in order of LEFT RIGHT TOP BOTTOM)
	//Side to side sentinels (WHITE Player)
	Node sLeft(WHITE); //INDEX IN NODES[] = (hexSize)^2
	nodes.push_back(sLeft);
	numNodes++;
	for(int i = 0; i < size;i++)
	{
		Edge sEdge(i*size, numNodes-1, 1, WHITE);
		nodes[i*size].append(sEdge);
		nodes[numNodes-1].append(sEdge);
		edges.push_back(sEdge);
	}
	
	Node sRight(WHITE); //INDEX IN NODES[] = (hexSize)^2 +1
	nodes.push_back(sRight);
	numNodes++;
	for(int i = 0; i < size;i++)
	{
		Edge sEdge(size*i+size-1, numNodes-1, 1, WHITE);
		nodes[size*i+size-1].append(sEdge);
		nodes[numNodes-1].append(sEdge);
		edges.push_back(sEdge);
	}
	//Top to bottom sentinels (BLACK Player)
	Node sTop(BLACK); //INDEX IN NODES[] = (hexSize)^2+2
	nodes.push_back(sTop);
	numNodes++;
	for(int i = 0; i < size;i++)
	{
		Edge sEdge(i, numNodes-1, 1,BLACK);
		nodes[i].append(sEdge);
		nodes[numNodes-1].append(sEdge);
		edges.push_back(sEdge);
	}
	
	Node sBot(BLACK); //INDEX IN NODES[] = (hexSize)^2+3
	nodes.push_back(sBot);
	numNodes++;
	for(int i = (size*size)-1; i >= size*(size-1); i--)
	{
		Edge sEdge(i, numNodes-1, 1, BLACK);
		nodes[i].append(sEdge);
		nodes[numNodes-1].append(sEdge);
		edges.push_back(sEdge);
	}
	
	//printNodes();
	//printEdges();
	//printOffset();
}

Graph::Graph(int numNodes, double den)
{
	//setting fields
	this->numNodes = numNodes;
	this->density = den;

	//init the vector of Nodes
	nodes.resize(numNodes);

	//randomly compute edges until density is ~= den
	int edgeCnt = 0;
	int totalPossibleEdges = numNodes*(numNodes-1)/2;
	srand(time(NULL));
	while((static_cast<double>(edgeCnt)/static_cast<double>(totalPossibleEdges) < den))
	{
		int x = (rand() % numNodes);
		int y = (rand() % numNodes);

		//search through edges vector to make sure this is a new edge
		bool valid = true;

		if(x==y){valid = false;} //dont include loopbacks
		for(int i = 0; i < edges.size(); i++)
		{
			if((edges[i].get1() == x && edges[i].get2() == y) || (edges[i].get2() == x && edges[i].get1() == y))
			{
				valid = false;
			}
		}
		if(valid)
		{
			Edge e(x,y,(rand() % 10)+1, static_cast<Color>(rand() % 2));
			edges.push_back(e); //puts on master edge vector

			nodes[x].append(e); //puts on edge list for each of the nodes
			nodes[y].append(e);

			edgeCnt++;
		}

	}
	//printEdges();
	//printNodes();

}

//Constructor to read input for HW3
Graph::Graph(char* inFile)
{
	ifstream ifp(inFile, ios::in);
	if(!ifp.is_open())
	{
		cerr << "File could not be found. Make sure input file is in same dir"<<endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		string num;
		getline(ifp, num);
		numNodes = atoi(num.c_str());
		//cout<<numNodes<<endl;

		nodes.resize(numNodes);

		while(!ifp.eof())
		{
			string line;
			getline(ifp,line);
			istringstream iss(line);
			int inVals[4];
			int i = 0;
			while(i != 4)
			{
				string s;
				getline(iss,s,' ');
				//cout<<s<<' ';
				inVals[i] = atoi(s.c_str());
				i++;
			}
			Edge e(inVals[0],inVals[1],inVals[2],static_cast<Color>(inVals[3]));

			edges.push_back(e); //puts on master edge vector
			nodes[inVals[0]].append(e); //puts on edge list for each of the nodes
			nodes[inVals[1]].append(e);

			//cout<<endl;
		}
		ifp.close();
	}

	//printEdges();
	//printNodes();

}

Node Graph::getNodeAt(int i)
{
	return nodes[i];
}

void Graph::printEdges()
{
	cout<<"\nEdges\n----------\n"<<"\nN1  N2  W  C"<<endl;
	for(int i = 0;i < edges.size();i++)
		{
			cout <<setfill('0')<<setw(3)<< edges[i].get1() <<' '<<setw(3)<< edges[i].get2()
				<<' '<<setw(2)<<edges[i].getW() <<' '<<setw(1)<< edges[i].getC()<<endl;
		}
	cout<<'\n';
}

void Graph::printNodes()
{
	cout<<"\nNode#  Dist"<<endl;
	for(int i = 0; i < nodes.size();i++)
	{
		cout<<setfill(' ')<<setw(3)<<i<<"    ";//<<nodes[i].getTempDist();
		if(nodes[i].getTempDist() == numeric_limits<int>::max())
		{
			cout<<"INFINITY";
		}
		else
		{
			cout<<nodes[i].getTempDist();
		}
		cout<<" Connected to: ";
		for(int j = 0; j < nodes[i].getListSize();j++)
		{
			cout<<nodes[i].getNodeAt(j,i)<<' ';
		}
		cout<<nodes[i].getPlayer()<<endl;
	}

	cout<<'\n';
}

void Graph::printOffset()
{
	cout << "HEX BOARD:"<<endl<<endl;
	string white = "WHITE";
	const char* wht = white.c_str();
	int whtPos = 0;
	cout << "    ";
	for(int i = 0; i< hexSize;i++)
	{
		cout <<std::left<<setw(4)<<setfill(' ')<< i;
	}

	int charOffset = 1;
	for(int i = 0; i < numNodes-4;i++)
	{
		if(i/hexSize == (hexSize/2) -1 + whtPos    && whtPos  < strlen(wht))
		{
			cout << "     " << wht[whtPos];
			whtPos++;
		}
	
		if(i % hexSize == 0)
		{
			cout <<endl;
			for(int j = 0; j < charOffset;j++)
			{
				if(j == charOffset - 1)
				{
					cout <<setw(2)<< charOffset -1;
				}
				cout << "  ";
			}
			charOffset++;
		}

		if(nodes[i].getPlayer() == WHITE)
		{
			cout << "w   ";
		}
		else if(nodes[i].getPlayer() == BLACK)
		{
			cout <<"b   ";
		}
		else if(nodes[i].getPlayer() == NOCOLOR)
		{
			cout <<"o   ";
		}
		else cout <<"ERROR";
		
		if((i + 1)%hexSize == 0)
		{
			cout <<setw(2) << charOffset -2;
		}
	}
	cout << endl;
	for(int i = 0; i <charOffset;i++)
	{
		cout << "  ";
	}
	for(int i = 0; i< hexSize;i++)
	{
		cout <<std::left<<setw(4)<<setfill(' ')<< i;
	}
	cout <<endl<<endl;
	for(int i = 0; i <charOffset;i++)
	{
		cout << "  ";
	}
	for(int i = 0; i < hexSize/2;i++)
	{
		cout << "   ";
	}
	cout << "B L A C K" <<endl<<endl;
	
}

//Gets the value of smallest distance
int Graph::getSmallest()
{
	int s = numeric_limits<int>::max();
	for(int i = 0;i<numNodes;i++)
	{
		if((s > nodes[i].getTempDist()) && !nodes[i].getVisited())
		{
			s = nodes[i].getTempDist();
		}
	}
	return s;
}


//Gets the index of the smallest
int Graph::getSmallestIndex()
{
	int s = 0;
	int j = 0;
	bool done = false;
	while(!done && j<numNodes) //gets the first nonvisited node
	{
		if(!nodes[j].getVisited())
		{
			s = j;
			done = true;
		}
		j++;
	}
	for(int i = 1;i<numNodes;i++) //compares this node to all the other nodes
	{
		if((nodes[s].getTempDist() > nodes[i].getTempDist()) && !nodes[i].getVisited())
		{
			s = i;
		}
	}
	return s;
}

void Graph::dijkstra(Color color)
{
	cout<<"\n\nONLY "<< ((color == RED) ? "RED" : "BLACK")<<"NODES"<<endl<<"---------------------------------------";
	int current = 0;//start at the first node
	nodes[current].setTDist(0); //set distance to 0 since we start here

	int visitedCounter = 0;

	while((visitedCounter < numNodes) && (getSmallest() != numeric_limits<int>::max())) //while there are unvisited nodes and the smallest dist is not infinity
	{
		for(int i = 0;i<nodes[current].getListSize();i++) //for every node connected to the current, update their distance
		{
			if(!nodes[nodes[current].getNodeIndexFromEdgeAt(i,current)].getVisited() && nodes[current].getEdgeColor(i) == color) //if not visited and the right color
			{
				nodes[nodes[current].getNodeIndexFromEdgeAt(i,current)].addToTempDist(
							nodes[current].getWeightFromEdgeAt(i), nodes[current].getTempDist()); //update distance for node i
			}
		}
		nodes[current].setVisited(true);
		visitedCounter++;
		current = getSmallestIndex(); //set next current number
		//cout<<getSmallestIndex()<<endl;
	}
}

//Dijsktra's alg without color implementation, it is the same as above except no color stuff
void Graph::dijkstra()
{
	cout<<"\n\nALL NODES"<<endl<<"---------------------------------------";
	int current = 0;
	nodes[current].setTDist(0);

	int visitedCounter = 0;

	while((visitedCounter < numNodes) && (getSmallest() != numeric_limits<int>::max()))
	{
		for(int i = 0;i<nodes[current].getListSize();i++)
		{
			if(!nodes[nodes[current].getNodeIndexFromEdgeAt(i,current)].getVisited()) //&& nodes[current].getEdgeColor(i) == color)
			{
				nodes[nodes[current].getNodeIndexFromEdgeAt(i,current)].addToTempDist(
							nodes[current].getWeightFromEdgeAt(i), nodes[current].getTempDist());
			}
		}
		nodes[current].setVisited(true);
		visitedCounter++;
		current = getSmallestIndex();
		//printNodes();
		//cout<<getSmallestIndex()<<endl;

	}
}

//Prints the average path calculated from Dijkstra's alg
void Graph::printAvg()
{
	int sum = 0;
	int j = 0; //declaring here b/c i need it for the AVG calculation.
	for(int i=0;i<numNodes;i++)
	{
		if(nodes[i].getTempDist() < numeric_limits<int>::max())
		{
			sum+=nodes[i].getTempDist();
			j++;
		}
	}
	cout<<"\n% OF NODES CALCULATED: "<<100*static_cast<double>(j)/static_cast<double>(numNodes)<<'%'<<endl;
	cout<<"AVERAGE PATH LENGTH: "<<static_cast<double>(sum)/static_cast<double>(j)<<endl;
}

//resets the nodes after Dijkstra's alg.
void Graph::resetNodes()
{
	for(int i = 0;i < numNodes;i++)
	{
		nodes[i].setTDist(numeric_limits<int>::max());
		nodes[i].setVisited(false);
	}
}

//Finds the set of a particular node. 
int Graph::findSet(vector<set<Node*> > setList, Node& n)
{
	int setNum = -1;
	for(int i = 0; i < setList.size(); i++)
	{
		if(setList[i].find(&n) != setList[i].end())
		{
			setNum = i;
		}
	}
	return setNum;
}

vector<set<Edge> > Graph::kruskal()
{
	//printEdges();
	//printNodes();

	//Setting up the colored edge inclusion/exclusion
	cout<<"Please Specify Colors (r,g,b)(space separated values (eg:r g b)): "; //asking user for input
	string x = "";
	getline(cin, x);
	set<Color> colors;
	istringstream iss(x);
	string col;
	while(getline( iss, col, ' ' )) //using the delimiter ' ' insert specified colors into a set.
	{
		colors.insert(getColor(col));
	}

	//make new edge vector that only includes the correct colored edges
	vector<Edge> usrDefColoredEdges;
	for(vector<Edge>::iterator j = edges.begin(); j != edges.end(); j++)
	{
		if(colors.find((*j).getC()) != colors.end()) //if the color of this edge is in the user specified
		{											//colors, add it to this vector
			usrDefColoredEdges.push_back((*j));
		}
	}


	//Algorithm part
	stable_sort(usrDefColoredEdges.begin(),usrDefColoredEdges.end()); // sorts edges by weight
	//note: i was using just regular sort() but it was messing up and giving me seg faults
	//i think it is because of a problem with my operator overloading, but for some reason stable_sort() works.
	//so whatever~

	//prints out sorted vector
	/*for(vector<Edge>::iterator i = usrDefColoredEdges.begin(); i != usrDefColoredEdges.end(); i++)
	{
		cout << *i << endl;
	}*/


	vector<set<Node*> > setList(numNodes); //list of all our sets (trees)
	vector<set<Edge> > forest; //a list of sets that correspond to connected subgraphs in the tree.
	
	for(int i = 0; i < numNodes;i++) //make every node its own set (tree)
	{
		set<Node*> singleNodeSet;
		singleNodeSet.insert(&nodes[i]);
		setList[i] = singleNodeSet;
	}

	for(vector<Edge>::iterator j = usrDefColoredEdges.begin(); j != usrDefColoredEdges.end(); j++) //for each sorted edge. going in ascending order.
	{
		int set1 = findSet(setList, nodes[(*j).get1()]);
		int set2 = findSet(setList, nodes[(*j).get2()]);
		if(set1 != set2) //if not in same set
		{

			//union the 2 sets
			setList[set1].insert(setList[set2].begin(),setList[set2].end());
			setList.erase(setList.begin() + set2);
	

			//accounts for not connected subgraphs where Kruskal's alg gives us multiple partial spanning trees
			//essentially we have a vector of sets, which represent trees
			//if we have decided to include this edge, which is from the if(set1==set2) statement
			//above, we put that edge in one tree in the forest. this code searches the forest(each tree in it)
			//and either inserts into the correct tree, or creates a new one if it is disconnected.
			if(forest.size() != 0)
			{
				bool wasInserted = false;
				for(vector<set<Edge> >::iterator k = forest.begin(); k != forest.end();k++)
				{
					bool done = false;
					for(set<Edge>::iterator p = (*k).begin(); p != (*k).end();p++)
					{
						if(((*p).get1() == (*j).get1()) || ((*p).get1() == (*j).get2()) || ((*p).get2() == (*j).get1()) || ((*p).get2() == (*j).get2()))
						{
							//if any of the nodes match up to the node we a currently looking at, insert into this tree.
							(*k).insert((*j));
							done = true;
							wasInserted = true;
							break;
						}
					}
					if(done) break;
				}
				if(!wasInserted) //if we couldn't find a match for the edge, create a new tree.
				{
					//cout << "Created new set of " << *j << " and inserted into forest" << endl;
					set<Edge> s;
					s.insert(*j);
					forest.push_back(s);
				}

			}
			else //initial condition, if forest is empty, create a tree and put it in the forest.
			{
				//cout << "Created new forest " << *j <<  endl;
				set<Edge> s;
				s.insert(*j);
				forest.push_back(s);
			}
			
		}
		/*This part unions 2 trees together from the forest. This is what happens when we
			consider an edge that borders between 2 already existing trees. We need to merge.
		*/
		bool done = false;
		for(int i = 0; i < forest.size();i++)
		{
			for(set<Edge>::iterator j = forest[i].begin();j!=forest[i].end();j++)
			{
				for(int k = i+1;k < forest.size();k++)
				{
					for(set<Edge>::iterator l = forest[k].begin();l!=forest[k].end();l++)
					{
						if((*j).get1() == (*l).get1() || ((*j).get1() == (*l).get2()) || ((*j).get2() == (*l).get1()) || ((*j).get2() == (*l).get2()))
						{
							
							for(set<Edge>::iterator u = forest[k].begin(); u != forest[k].end(); u++)
							{
								forest[i].insert(*u);
							}
							forest.erase(forest.begin()+k);
							done = true;
							break;
						}
						if(done) break;
					}
					if(done) break;
				}
				if(done) break;
			}
		}
		
		
	}
	return forest;
}

bool Graph::isColoringValid(int x,int y)
{
	if(nodes[y*hexSize + x].getPlayer() == NOCOLOR)
	{
		return true;
	}
	else return false;
}

void Graph::setColor(int x,int y, Color c)
{
	nodes[y*hexSize + x].setPlayer(c);
	for(int i = 0; i < nodes[y*hexSize +x].getListSize();i++)
	{
		int connectedTo = nodes[y*hexSize + x].getNodeAt(i,y*hexSize + x);
		nodes[y*hexSize + x].setEdgeColor(i, c);
		nodes[connectedTo].setEdgeColor(nodes[connectedTo].getEdgeIndexFromList(y*hexSize+x), c);
	}
}

bool Graph::sentinelPathComplete()
{
	//Depth first search from left to right
	if(DFS(hexSize*hexSize, hexSize*hexSize +1, WHITE))
	{
		cout << "White Player Wins!"<<endl;
		resetNodes();
		return true;
	}
	else if(DFS(hexSize*hexSize + 2, hexSize*hexSize +3, BLACK))
	{
		cout << "Black Player Wins!"<<endl;
		resetNodes();
		return true;
	}
	else 
	{
		resetNodes();
		return false;
	}
}

Color Graph::sentinelPathCompleteWithColor()
{
	//Depth first search from left to right
	if(DFS(hexSize*hexSize, hexSize*hexSize +1, WHITE))
	{
		resetNodes();
		return WHITE;
	}
	else if(DFS(hexSize*hexSize + 2, hexSize*hexSize +3, BLACK))
	{
		resetNodes();
		return BLACK;
	}
	else 
	{
		resetNodes();
		return NOCOLOR;
	}
}

inline bool Graph::DFS(int start, int target, Color col)
{
	//cout << "start: " << start << " target: "<<target<<endl;
	stack<int> search;
	search.push(start);
	//cout << "stack.top: " <<  search.top() << endl;
	
	while(!search.empty())
	{
		int currentNode = search.top();
		//cout << "loop" << endl<<"size at start of loop: " <<search.size()<<endl;
		search.pop();
		if(currentNode == target)
			return true;
		nodes[currentNode].setVisited(true);
		for(int i = 0; i < nodes[currentNode].getListSize(); i++)
		{
			if(nodes[currentNode].getEdgeColor(i) == col &&
				 nodes[nodes[currentNode].getNodeAt(i,currentNode)].getPlayer() == col &&
				 	!nodes[nodes[currentNode].getNodeAt(i,currentNode)].getVisited()	)
			{
				//cout << "top before push: " << search.top()<<endl;
				search.push(nodes[currentNode].getNodeAt(i,currentNode));
				//cout << "pushed: "<< nodes[currentNode].getNodeAt(i,currentNode) << endl;
				//cout << "new top = "<<search.top() <<endl;
			}
		}
	}
	return false;
}





















