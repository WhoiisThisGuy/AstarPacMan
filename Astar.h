/* Includes from Near */
#include "Map.h"
// A C++ Program to implement A* Search Algorithm 
#include<stack>
#include<set>
#include<iostream>

// Creating a shortcut for int, int pair type 
typedef std::pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type 
typedef std::pair<double, std::pair<int, int>> pPair;

// A structure to hold the neccesary parameters 
struct cell
{
	// Row and Column index of its parent 
	// Note that 0 <= i <= MAPSIZEX-1 & 0 <= j <= MAPSIZEY-1 
	int parent_i, parent_j;
	// f = g + h 
	double f, g, h;
};

int aStarSearch(Pair src, Pair dest, std::stack<Pair>& Path);
std::stack<Pair> tracePath(cell cellDetails[][MAPSIZEY], Pair dest);