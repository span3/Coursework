#include <cfloat>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "graph.h"

using namespace std;

enum COLORS {
	WHITE, BLACK, NONE
};

double dRand(double min, double max) {
	double d = (double) rand() / RAND_MAX;
	return min + d * (max - min);
}

Graph::Graph(int n) {
	p_win = false;
	c_win = false;
	int o = n * n;
	order = o;
	size = 0;
	vertices.resize(o + 4);
	TOP = o;
	BOTTOM = o + 1;
	LEFT = o + 2;
	RIGHT = o + 3;
	board.resize(n);
	std::vector<vector<COLORS> >::iterator it;
	//initialize board to have all empty spaces
	for (it = board.begin(); it != board.end(); ++it) {
		it->resize(n);
	}
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			board[x][y] = NONE;

			//DEBUG
			//if (x==2 && y<10) board[x][y] = WHITE;
		}
	}
	std::vector<Vertex>::iterator x;
	for (x = vertices.begin(); x != vertices.end(); ++x) {
		x->sub_id = -1.0;
		x->color = 0;
	}
	/*
	 for (int i = 0; i < o+4; ++i) {
	 //vertices[i].neighbors.resize(o);
	 vertices[i].sub_id = -1.0;
	 vertices[i].color = 0;
	 
	 for (int j = 0; j < o; ++j) {
	 vertices[i].neighbors[j].distance = -1.0;
	 }
	 
	 }
	 */
}

Graph::~Graph() {
}  //would delete something if i used the new keyword in my constructer

//edge color back == 0, red == 1, both == 2
//vertex color back == 0, grey == 1, white == 2
bool Graph::addEdge(int u, int v, double distance, int edgeColor) {
	if (testEdge(u, v))
		return false; //return false if edge already exists
	vertices[u].neighbors[v].distance = distance;
	vertices[u].neighbors[v].color = edgeColor;
	vertices[u].neighbors[v].v1 = u;
	vertices[u].neighbors[v].v2 = v;
	vertices[v].neighbors[u].distance = distance;
	vertices[v].neighbors[u].color = edgeColor;
	vertices[v].neighbors[u].v1 = v;
	vertices[v].neighbors[u].v2 = u;
	vertices[u].neighbors[v].inTree = false;
	vertices[v].neighbors[u].inTree = false;
	vertices[u].sub_id = -1.0;
	vertices[v].sub_id = -1.0;
	edgeList.push_back(vertices[u].neighbors[v]);
	size++;
	return true;
}

inline bool Graph::testEdge(int u, int v) {
	if (vertices[u].neighbors[v].distance == -1.0)
		return false;
	return true;
}

void Graph::addRandom(double density, int dist) {
	int num_edges =
			static_cast<int>(getOrder() * (getOrder() - 1) * density / 2);
	for (int i = 0; i < num_edges; ++i) {
		int u = (rand() % getOrder());
		int v;
		do
			v = (rand() % getOrder());
		while (u == v);
		double distance = (1.0 * rand() / RAND_MAX * (dist - 1) + 1.0); //random(1, dist);
		int ec = rand() % 2;
		if (!addEdge(u, v, distance, ec))
			--i;
	}
}
//edge color black == 0, red == 1, both == 2
//vertex color black == 0, grey == 1, white == 2
void Graph::getShortestDist(int s, int edgeColor) { // s == source, d == destination
	for (int i = 0; i < getOrder(); i++) {
		vertices[i].distance = -1.0;
		vertices[i].color = 2;
	}
	vertices[s].distance = 0; // initialize all vertex distance to infinity (-1) and the source distance 0

	//while we still have vertices to visit
	while (isWhite()) {

		int u = getLowestDist();
		if (u == -1)
			break;
		for (int i = 0; i < getOrder(); i++) {
			if (vertices[u].neighbors[i].distance < 0)
				continue;
			double alt = vertices[u].neighbors[i].distance
					+ vertices[u].distance;
			if ((alt < vertices[i].distance || vertices[i].distance == -1)
					&& goodColor(vertices[u].neighbors[i].color, edgeColor)) {
				vertices[i].distance = alt;

			}

		}
		vertices[u].color = 0;
	}

}
//vertex color black == 0, grey == 1, white == 2
double Graph::getAverageDist(int edgeColor) {

	getShortestDist(1, edgeColor);
	double sum = 0;
	int count = 0;
	for (int i = 0; i < getOrder(); i++) {
		if (vertices[i].distance == -1.0)
			continue;
		sum += vertices[i].distance;
		count++;
	}
	return sum / count;
}

void Graph::readGraph() {
	ifstream fin("data.txt");
	string line;
	getline(fin, line);
	order = atoi(line.c_str());
	//cout << order << endl;
	//resize graph
	vertices.resize(order);
	for (int i = 0; i < order; ++i) {
		vertices[i].neighbors.resize(order);
		vertices[i].sub_id = -1.0;
		for (int j = 0; j < order; ++j) {
			vertices[i].neighbors[j].distance = -1.0;
		}
	}
	while (getline(fin, line)) {
		istringstream tokenizer(line);
		string token;
		getline(tokenizer, token, ' ');
		istringstream u_iss(token);
		int u;
		u_iss >> u;
		//cout << u << endl;
		getline(tokenizer, token, ' ');
		istringstream v_iss(token);
		int v;
		v_iss >> v;
		//cout << v << endl;
		getline(tokenizer, token, ' ');
		istringstream d_iss(token);
		int dist;
		d_iss >> dist;
		//cout << dist << endl;
		getline(tokenizer, token, ' ');
		istringstream c_iss(token);
		int color;
		c_iss >> color;
		//cout << color << endl;
		addEdge(u, v, dist, color);
	}
	cout << "Finished reading input file." << endl;
}

//simple sorting function that sorts all edges in edgeList in ascending order by distance
void Graph::sortEdges() {
	std::vector<Edge>::reverse_iterator i;
	std::vector<Edge>::iterator j;
	for (i = edgeList.rbegin(); i != edgeList.rend(); ++i) {
		for (j = edgeList.begin(); j != edgeList.end(); ++j) {
			if (j->distance > (j + 1)->distance) {
				std::iter_swap(j, j + 1);
			}
		}
	}

}

void Graph::getMST() {
	sortEdges();
	//int MST[getOrder()][getOrder()];
	bool tree[getOrder()];
	int sum = 0;
	for (int i = 0; i < getOrder(); ++i) {
		tree[i] = false;
	}
	//Objective - pick minimum index from set of verts, set the associated edge's inTree to true.
	//Loop through number of vertices
	cout << endl;
	cout << "MST using Prim's" << endl;
	for (int i = 0; i < getOrder(); ++i) {
		//While this index's vertice is unassigned
		if (tree[i] == false) {
			//create index and minimum counters
			int minIndex = 0;
			int min = INT_MAX;
			//loop through edgeList looking for vertice i
			for (int j = 0; j < getSize(); ++j) {
				//if vertice i is one of an edge's two verts, then that other vert is a neighbor
				//if that edge is greater than the current minimum, grab its distance and save its index
				if (i == edgeList[j].v1 && tree[edgeList[j].v1] == false) {
					if (min > edgeList[j].distance) {
						minIndex = j;
						min = edgeList[j].distance;
					}
				} else if (i == edgeList[j].v2
						&& tree[edgeList[j].v2] == false) {
					if (min > edgeList[j].distance) {
						minIndex = j;
						min = edgeList[j].distance;
					}
				}
			}
			tree[edgeList[minIndex].v1] = true;
			tree[edgeList[minIndex].v2] = true;
			cout << edgeList[minIndex].v1 << " -> " << edgeList[minIndex].v2
					<< " cost: " << min << endl;
			sum += min;
		}
	}
	cout << "total: " << sum << endl;
}

void Graph::initializeVerts() {
	for (int i = 0; i < getOrder(); ++i) {
		vertices[i].color = -1;
	}
}

void Graph::printBoard() {
	//cout << "in printBoard" << endl;
	cout << endl << "   ";
	for (int i = 0; i < (int) sqrt(getOrder()); ++i) {
		if (i < 10) {
			cout << i << "  ";
		} else {
			cout << i << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < (int) sqrt(getOrder()); ++i) {
		if (i < 10)
			cout << string(i + 1, ' ') << i << " ";
		else
			cout << string(i, ' ') << i << " ";
		for (int j = 0; j < (int) sqrt(getOrder()); ++j) {

			if (board[i][j] == NONE)
				cout << " *";
			else if (board[i][j] == WHITE)
				cout << " W";
			else if (board[i][j] == BLACK)
				cout << " B";
			cout << " ";
		}
		cout << endl;
	}
}

bool Graph::playerMove(int x, int y) {
	//cout << "in playerMove" << endl;
	if (board[x][y] == NONE) {
		board[x][y] = WHITE; //white is player

		if (y == 0) {
			//cout << "y is 0" << endl;
			Edge e;
			e.v2 = x * (sqrt(getOrder()) - 1) + y;
			e.v1 = LEFT;
			e.color = 0;
			edgeList.push_back(e);
			vertices[e.v2].neighbors.push_back(e);
			vertices[LEFT].neighbors.push_back(e);
			//cout << "connected to LEFT" << endl;
		}
		if (y == (sqrt(getOrder()) - 1)) {
			Edge e;
			e.v1 = RIGHT;
			e.v2 = x * (sqrt(getOrder()) - 1) + y;
			e.color = 0;
			edgeList.push_back(e);
			vertices[e.v2].neighbors.push_back(e);
			vertices[RIGHT].neighbors.push_back(e);
			//cout << "connected to RIGHT" << endl;
		}

	}
	//check if space is already occupied
	else if (board[x][y] == WHITE || board[x][y] == BLACK)
		return false;

	check_adjacent(x, y);
	return true;
}

bool Graph::computerMove(int turn) {
	//random move
	/*int x = rand()%11;
	 int y = rand()%11;
	 if (board[x][y] == NONE) {
	 cout << "computer move is (" << x << "," << y << ")" << endl;
	 board[x][y] = BLACK;
	 */
	if (turn < 3
			&& (board[0][(int) (sqrt(getOrder() - 1)) / 2] == NONE
					|| board[0][(int) (sqrt(getOrder() - 1)) / 2] == WHITE)) {
		if (board[0][(int) (sqrt(getOrder() - 1)) / 2] == NONE) {
			board[0][(int) (sqrt(getOrder() - 1)) / 2] = BLACK;
			Edge e;
			e.v2 = (int) (sqrt(getOrder() - 1) / 2) * (sqrt(getOrder() - 1));
			e.v1 = TOP;
			e.color = 0;
			edgeList.push_back(e);
			vertices[e.v2].neighbors.push_back(e);
			vertices[TOP].neighbors.push_back(e);
		} else if (board[0][(int) ((sqrt(getOrder() - 1)) / 2) + 1] == NONE) {
			board[0][(int) ((sqrt(getOrder() - 1)) / 2) + 1] = BLACK;
			Edge e;
			e.v2 = (int) ((sqrt(getOrder() - 1) / 2) + 1) * (sqrt(getOrder()));
			e.v1 = TOP;
			e.color = 0;
			edgeList.push_back(e);
			vertices[e.v2].neighbors.push_back(e);
			vertices[TOP].neighbors.push_back(e);
		}
	} else {
		for (int i = 0; i < sqrt(getOrder() - 1); ++i) { //i index keeps track of y location
			//cout << "i is not the problem" << endl;
			for (int j = 0; j < sqrt(getOrder()); ++j) { //j index keeps track of x location
				//cout << "j is not the problem" << endl;
				if (board[i][j] == BLACK) { //if we find a black value, make a value that connects to it
					//cout << "ij call is not the problem" << endl;
					for (int q = 0; q < sqrt(getOrder() - 1); ++q) { //q keeps track of current row's x
						//cout << "q is not the problem" << endl;
						bool rowTaken = false;
						for(int thisrow = 0; thisrow < sqrt(getOrder()-1); ++thisrow) {
							if(board[i+1][thisrow] == BLACK) {
								rowTaken = true;
								if(board[i+2][thisrow-1] == WHITE && board[i+2][thisrow] == WHITE && board[i+2][thisrow+1] == WHITE) {
									rowTaken = false;
								}
								if(board[i][thisrow-1] == WHITE && board[i][thisrow] == WHITE && board[i][thisrow+1] == WHITE) {
									rowTaken = false;
								}
							}
						}
						if(rowTaken == false) {
							if(board[i+1][q] == WHITE && board[i+1][q-1] == NONE &&q == j && q < sqrt(getOrder())-1) {
								board[i+1][q-1]==BLACK;						
								if (i+1 == sqrt(getOrder())-1) {
									Edge e;
									e.v1 = BOTTOM;
									e.v2 = q-1 * (sqrt(getOrder()) - 1) + i + 1;
									e.color = 0;
									edgeList.push_back(e);
									vertices[e.v2].neighbors.push_back(e);
									vertices[BOTTOM].neighbors.push_back(e);
									c_win = true;
									//cout << "connected to BOTTOM" << endl;
								}
								return true;
								
							} else if (board[i + 1][q] == NONE && q == j && q < sqrt(getOrder())-1) { //if current row's x 
							//is empty, add it, else check x+1 and x-1, else create a random value because
							//you're shit out of luck
								//cout << "q comp is not the problem" << endl;
								board[i + 1][q] = BLACK;
								if (i+1 == sqrt(getOrder())-1) {
									Edge e;
									e.v1 = BOTTOM;
									e.v2 = j * (sqrt(getOrder()) - 1) + i + 1;
									e.color = 0;
									edgeList.push_back(e);
									vertices[e.v2].neighbors.push_back(e);
									vertices[BOTTOM].neighbors.push_back(e);
									c_win = true;
									//cout << "connected to BOTTOM" << endl;
								}
								return true;
							} else if (board[i + 1][q] == NONE && q == j+1
									&& q < sqrt(getOrder()) - 1) {
								//cout << "q+1 is not the problem" << endl;
								board[i + 1][q] = BLACK;
								if (i+1 == sqrt(getOrder())-1) {
									Edge e;
									e.v1 = BOTTOM;
									e.v2 = (j+1) * (sqrt(getOrder()) - 1) + i + 1;
									e.color = 0;
									edgeList.push_back(e);
									vertices[e.v2].neighbors.push_back(e);
									vertices[BOTTOM].neighbors.push_back(e);
									c_win = true;
									//cout << "connected to BOTTOM" << endl;
								}
								return true;
							} else if (board[i + 1][q-1] == NONE && q-1 == j
									&& q > -1 && board[i+1][q+1] != WHITE) {
								//cout << "q-1 is not the problem" << endl;
								board[i + 1][q-1] = BLACK;
								if (i+1 == sqrt(getOrder())-1) {
									Edge e;
									e.v1 = BOTTOM;
									e.v2 = (j-1) * (sqrt(getOrder()) - 1) + i + 1;
									e.color = 0;
									edgeList.push_back(e);
									vertices[e.v2].neighbors.push_back(e);
									vertices[BOTTOM].neighbors.push_back(e);
									c_win = true;
									//cout << "connected to BOTTOM" << endl;
								}
								return true;
							} else if(board[i][q+1] == NONE && q+1 < sqrt(getOrder())-1 && board[i+1][q-1] == WHITE && board[i+1][q] == WHITE) {
								board[i][q+1] = BLACK;
								return true;
							} else if(board[i+1][j] == WHITE && board[i+1][j-1] == NONE && j-1 > -1) {
								board[i+1][j-1] = BLACK;
								if (i+1 == sqrt(getOrder())-1) {
									Edge e;
									e.v1 = BOTTOM;
									e.v2 = (j-1) * (sqrt(getOrder()) - 1) + i + 1;
									e.color = 0;
									edgeList.push_back(e);
									vertices[e.v2].neighbors.push_back(e);
									vertices[BOTTOM].neighbors.push_back(e);
									c_win = true;
									//cout << "connected to BOTTOM" << endl;
								}
								return true;
							}
						}
					}
				}
			}
		}
	}

	//cout << "y is 0" << endl;

	//else if (board[x][y] == WHITE || board[x][y] == BLACK) return false;

	//check_adjacent(x, y);
	return true;
}

bool Graph::pie_rule(int x, int y) {
	if ((x < ((int) (((sqrt(getOrder() - 1)) + 1) / 2) + 2))
			&& (x > ((int) (((sqrt(getOrder() - 1)) + 1) / 2) - 2))
			&& (y < ((int) (((sqrt(getOrder() - 1)) + 1) / 2) + 2))
			&& (y > ((int) (((sqrt(getOrder() - 1)) + 1) / 2) - 2))) {
		cout << "computer chooses to swap!" << endl;
		board[x][y] = BLACK;
		return true;
	} else {
		cout << "computer chooses to move!" << endl;
		return false;
	}
}

void Graph::check_adjacent(int x, int y) {
	//FOR EACH ADJACENT VERTEX
	//CHECK IF ANY OF THEM ARE THE SAME COLOR AS THE CURRENT
	//IF SO, CREATE AN EDGE BETWEEN THEM
	//ELSE GO ONTO THE NEXT
	Edge e;
	e.color = 0;
	//cout << "declared edge" << endl;
	if (x > 0 && board[x - 1][y] == board[x][y]) {
		e.v2 = (x - 1) * (sqrt(getOrder()) - 1) + y;
		e.v1 = x * (sqrt(getOrder()) - 1) + y;
		//cout << "made edge" << endl;
		edgeList.push_back(e);
		vertices[e.v1].neighbors.push_back(e);
		//e.v2 = x*(sqrt(getOrder()) -1) + y;
		//e.v1 = (x-1)*(sqrt(getOrder()) -1) + y;
		vertices[e.v2].neighbors.push_back(e);
		//cout << "added edge between adjacent pieces" << endl;
	}
	if (x < (sqrt(getOrder()) - 1) && board[x + 1][y] == board[x][y]) {
		e.v2 = (x + 1) * (sqrt(getOrder()) - 1) + y;
		e.v1 = x * (sqrt(getOrder()) - 1) + y;
		//cout << "made edge" << endl;
		edgeList.push_back(e);
		vertices[e.v1].neighbors.push_back(e);
		//e.v2 = x*(sqrt(getOrder()) -1) + y;
		//e.v1 = (x+1)*(sqrt(getOrder()) -1) + y;
		vertices[e.v2].neighbors.push_back(e);
		//cout << "added edge between adjacent pieces" << endl;
	}
	if (y < (sqrt(getOrder()) - 1) && board[x][y + 1] == board[x][y]) {
		e.v2 = x * (sqrt(getOrder()) - 1) + (y + 1);
		e.v1 = x * (sqrt(getOrder()) - 1) + y;
		//cout << "made edge" << endl;
		edgeList.push_back(e);
		vertices[e.v1].neighbors.push_back(e);
		//e.v2 = x*(sqrt(getOrder()) -1) + y;
		//e.v1 = x*(sqrt(getOrder()) -1) + (y+1);
		vertices[e.v2].neighbors.push_back(e);
		//cout << "added edge between adjacent pieces" << endl;
	}
	if (y > 0 && board[x][y - 1] == board[x][y]) {
		e.v2 = x * (sqrt(getOrder()) - 1) + (y - 1);
		e.v1 = x * (sqrt(getOrder()) - 1) + y;
		//cout << "made edge" << endl;
		edgeList.push_back(e);
		vertices[e.v1].neighbors.push_back(e);
		//e.v2 = x*(sqrt(getOrder()) -1) + y;
		//e.v1 = x*(sqrt(getOrder()) -1) + (y-1);
		vertices[e.v2].neighbors.push_back(e);
		//cout << "added edge between adjacent pieces" << endl;
	}
	if (x > 0 && y < (sqrt(getOrder()) - 1)
			&& board[x - 1][y + 1] == board[x][y]) {
		e.v2 = (x - 1) * (sqrt(getOrder()) - 1) + (y + 1);
		e.v1 = x * (sqrt(getOrder()) - 1) + y;
		//cout << "made edge" << endl;
		edgeList.push_back(e);
		vertices[e.v1].neighbors.push_back(e);
		//e.v2 = x*(sqrt(getOrder()) -1) + y;
		//e.v1 = (x-1)*(sqrt(getOrder()) -1) + (y+1);
		vertices[e.v2].neighbors.push_back(e);
		//cout << "added edge between adjacent pieces" << endl;
	}
	if (x < (sqrt(getOrder()) - 1) && y > 0
			&& board[x + 1][y - 1] == board[x][y]) {
		e.v2 = (x + 1) * (sqrt(getOrder()) - 1) + (y - 1);
		e.v1 = x * (sqrt(getOrder()) - 1) + y;
		//cout << "made edge" << endl;
		edgeList.push_back(e);
		vertices[e.v1].neighbors.push_back(e);
		//e.v2 = x*(sqrt(getOrder()) -1) + y;
		//e.v1 = (x+1)*(sqrt(getOrder()) -1) + (y-1);
		vertices[e.v2].neighbors.push_back(e);
		//cout << "added edge between adjacent pieces" << endl;
	}
}

//check win using Depth-First Search
void Graph::checkWin(COLORS c) {
	//check if there is a path of white tiles starting from x==0 to x==max
	//check if there is a path of black tiles starting from y==0 to y==max
	//cout << "in checkWin, calling rec fcn" << endl;
	//check LEFT to RIGHT
	if (c == WHITE)
		checkWin_rec(LEFT, RIGHT);
	else if (c == BLACK)
		checkWin_rec(BOTTOM, TOP);

	//cout << "win? " << game_win << " resetting colors" << endl;
	//set all colors back to unexplored
	std::vector<Vertex>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); ++it) {
		it->color = 0;
		std::vector<Edge>::iterator z;
		for (z = it->neighbors.begin(); z != it->neighbors.end(); ++z) {
			z->color = 0;
		}
	}
	std::vector<Edge>::iterator k;
	for (k = edgeList.begin(); k != edgeList.end(); ++k) {
		k->color = 0;
	}

	//if (c == WHITE && p_win == true) cout << "player has won!" << endl;
	//else if (c == BLACK && c_win == true) cout << "computer has won!" << endl;

}

//EDGE COLORS: 0 = unexplored, 1 = explored, 2 = discovery, 3 = back
//VERTEX COLORS: 0 = unexplored, 1 = explored

void Graph::checkWin_rec(int s, int e) {
	//cout << "in checkWin_rec" << endl;
	//label as explored
	vertices[s].color = 1;
	std::vector<Edge>::iterator it;
	for (it = vertices[s].neighbors.begin(); it != vertices[s].neighbors.end();
			++it) {
		//cout << "checking neighbors" << endl;
		//if edge is unexplored
		if (it->color == 0) {
			//cout << "unexplored edge" << endl;
			//Vertex w = vertices[it->v2];
			//if we reached the other end, player wins
			if (it->v1 == e || it->v2 == e) {
				cout << "found path!" << endl;
				if (e == RIGHT)
					p_win = true;
				else if (e == BOTTOM)
					c_win = true;
				return;
			}
			//if loop, return
			/*
			 if (it->v1 == s) {
			 cout << "encountered loop" << endl;
			 return;
			 }
			 */
			//if vertex is unexplored
			if (vertices[it->v2].color == 0) {
				//label edge as discovery edge
				it->color = 2;
				//cout << "rec call for v2 " << it->color << endl;
				//recursive call
				checkWin_rec(it->v2, e);
			}
			//may not need
			else if (vertices[it->v1].color == 0) {
				//label edge as discovery edge
				it->color = 2;
				//cout << "rec call for v1 " << it->color << endl;
				//recursive call
				checkWin_rec(it->v1, e);
			}
			//else label edge as back edge
			else {
				//cout << "labeling as back edge" << endl;
				it->color = 3;
			}
		}
	}
}

bool Graph::isWhite() {
	for (int i = 0; i < getOrder(); i++)
		if (vertices[i].color == 2)
			return true;
	return false;
}

int Graph::getLowestDist() {
	double current = DBL_MAX;
	int node = -1;
	for (int i = 0; i < getOrder(); i++) {
		if (vertices[i].color != 2)
			continue; //to next iteration
		if (vertices[i].distance == -1.0)
			continue;
		if (vertices[i].distance < current) {
			node = i;
			current = vertices[i].distance;
		}
	}
	return node;
}

bool Graph::goodColor(int edgeColor, int testColor) {
	if (testColor == 2)
		return true;
	if (edgeColor == testColor)
		return true;
	return false;
}

