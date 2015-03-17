/*node.h file*/
#ifndef NODE_H
#define NODE_H

class Node {
private:
	static const int size = 50; // Number of nodes/edges (prevents magic numbers)
	int connected[size]; // Keeps track of all the nodes that are connected to this one
	int Counter;                   // Keeps the current index of connected[]
	bool visit; // Tells if we visited the node. True means we have, false means we haven't

public:

	/*******Node constructor******/
	Node() {
		Counter = 0;
		visit = false;
	}

	// Adds a connected node to current node
	// using the node id
	void connect(int node) {
		connected[Counter] = node;
	}

	// Returns visit
	bool getVisit() {
		return visit;
	}
	// switches visit logic. If it was true it changes
	// to false and vice versa
	void switchBool() {
		visit = !visit;
	}

	// Checks to see if there are any connections to
	// this node.
	bool hasConnection() {
		return (Counter != 0);
	}

	// Returns counter
	int getCounter() {
		return Counter;
	}

	// Returns the next connected node.
	// Usually decrement before we call
	// getConnected()
	int getConnected() {
		return connected[Counter];
	}

	// Increments the counter
	void increaseCounter() {
		Counter++;
	}

	// Decrements the counter
	void decreaseCounter() {
		Counter--;
	}

	// Sets the counter to a given int x
	void setCounter(int x) {
		Counter = x;
	}

	// Inputs value into the connected[]
	void inputConnected(int value) {
		connected[Counter] = value;
	}
};

#endif



