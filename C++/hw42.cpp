void playerTurn(Graph* graph) {
  int x, y;
  int valid = 0;
  while (valid == 0) {
    do {
      cout << "Enter row coordinate: ";
      cin >> x;
    } while (!cin || x <= 0 || x > graph->getSize());
    do {
	  cout << "Enter col coordinate: ";
	  cin >> y;
    } while (!cin || y <= 0 || y > graph->getSize());
	if (graph->nodeList[(x-1) * graph->getSize() + y-1]->getStatus() == 0) {
	  valid = 1;
      graph->nodeList[(x-1)*graph->getSize() + y-1]->setStatus(1);
	}
	else {
	  cout << "This spot is taken, please enter another" << endl;
	}
  }
}

void computerTurn(Graph* graph, int firstTurn) {
  int x, y;
  int valid = 0;
  while (valid == 0) {
    x = rand() % graph->getSize();
    y = rand() % graph->getSize();
	if (graph->nodeList[ x*graph->getSize() + y]->getStatus() == 0) {
	  valid = 1;
      graph->nodeList[ x*graph->getSize() + y]->setStatus(2);
    }
  }
  if (firstTurn == 1) {
    graph->printGraph();
    int pie;
    do {
      cout << "Enter 1 to switch places, 0 to proceed: ";
   	  cin >> pie;
    } while (!cin || pie < 0 || pie > 1);
    if (pie == 1) {
      graph->nodeList[ x*graph->getSize() + y]->setStatus(1);
	  computerTurn(graph, 0);
	  graph->printGraph();
    }
  }
}

void declareWinner (int winner) {
  if (winner == 1) cout << endl << "You win!!!" << endl;
  else if (winner == 2) cout << endl << "The computer wins...better luck next time" << endl;
  exit(0);
}

int main() {
  srand(time(NULL));
  int sizeOf, choice, pie;
  int firstTurn = 1;
  int done = 0;
  cout << "**********************************************************************" << endl;
  cout << "* Welcome to the game of Hex! Your goal is to form a horizontal line *" << endl;
  cout << "* before your opponent can form a vertical line.                     *" << endl;
  cout << "**********************************************************************" << endl << endl;
  cout << "Enter desired board size: ";
  cin >> sizeOf;
  Graph* graph = new Graph(sizeOf);
  graph->insertEdge();
  graph->printGraph();
  do {
    cout << "Enter 1 to go first, 0 to go second: ";
    cin >> choice;
  } while (!cin || choice < 0 || choice > 1);
  if (choice == 1) {
    firstTurn = 0;
    playerTurn(graph);
	computerTurn(graph,firstTurn);
	graph->printGraph();
  }
  else {
    computerTurn(graph, firstTurn);
	firstTurn = 0;
  }
  while (done == 0) {
    playerTurn(graph);
	if (graph->checkDone(1) == 1) declareWinner(1);
	computerTurn(graph, 0);
	if (graph->checkDone(2) == 2) declareWinner(2);
	graph->printGraph();
  }
  graph->printGraph();
}