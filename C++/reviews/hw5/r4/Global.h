#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
using namespace std;

/*
 * A global class used so that these variables could be used universally throughout the document
 * Made them in a class so that it is a bit neater than just putting them floating in space
 */
class _GLOBAL{
public:
        static bool playerOneMovedFirst;
        static bool firstTurn;
	//Number of iterations to do
	static const int I_NUM;
	static const int INFINITY;
	static const int SIZE;
	static const vector<int> INFINITY_VECTOR;
};
bool _GLOBAL::playerOneMovedFirst = false;
bool _GLOBAL::firstTurn = true;
//Number of iterations to do
const int _GLOBAL::I_NUM = 1000;
const int _GLOBAL::SIZE = 11;
const int _GLOBAL::INFINITY = numeric_limits<int>::max();
const vector<int> _GLOBAL::INFINITY_VECTOR(_GLOBAL::SIZE, _GLOBAL::INFINITY);
