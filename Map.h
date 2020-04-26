#include <SFML\Graphics.hpp>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace sf;
using std::string;
using std::vector;

#ifndef MAP_H
#define MAP_H

#define MAPOFFSET 4*24 //Needed this for the start positions of the characters
#define MAPWIDTH 28
#define MAPSIZEX 28 //not used just to remember
#define MAPSIZEY 31 //not used just to remember
#define CELLSIZE 24.0f


class Map
{

public:
	Map();
	~Map();
	void Update();

	static char GetTile(int x, int y);
	

private:

	static string level;
	float CellSize;
	unsigned int uCellSize;

private:
	void LoadMap();

};

#endif