//#pragma once
//#include "Map.h"
//#include <list> 
//#include <iterator>
//#include <iostream> 
//
//class Astar
//{
//
//public:
//	Astar();
//
//private:
//
//	struct Coordinate {
//
//		int x, y;
//
//	};
//
//	struct node
//	{
//		int parentX;
//		int parentY;
//		int posX, posY;
//		double f, g, h;
//	};
//
//private:
//
//	inline float ManHattan(int x, int y, Coordinate goal) { //Manhattan heurisztika
//	
//		return (goal.x - x) + (goal.y - y);
//	}
//
//	void createPath(node AstarArray[MapArraySizeX][MapArraySizeY],Coordinate goal, Coordinate start);
//	bool isFreeCell();
//	bool StandardAstar(int MapArray[MapArraySizeX][MapArraySizeY], Coordinate start, Coordinate goal);
//	void lookforsmallestF(std::list<node>& openlist, node* tempNode);
//};
//
