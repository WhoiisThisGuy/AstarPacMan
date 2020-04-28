#include <SFML\Graphics.hpp>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <utility>

using namespace sf;
using std::string;
using std::to_string;
using std::vector;
using std::unordered_map;
using std::list;
using std::pair;

extern bool powerOn; //Defined in Map.cpp, only Map and Scatter, Chase, Frighten mods are using it.

#ifndef MAP_H

#define MAP_H

#define MAPOFFSET 4*24 //Needed this for the start positions of the characters
#define MAPWIDTH 28
#define MAPROWS 34 //not used just to remember
#define MAPCOLUMNS 28 //not used just to remember
#define CELLSIZE 24

extern int glob_numofPowerPellets;

class Map
{

public:
	Map();
	~Map();
	void Update();
	void Draw(RenderWindow &window);

	static char GetTile(int x, int y);

private:

	

	typedef struct pellet{
		
		bool ispowerPellet = false;
		pellet() {};
		pellet(int i, int j) {

			pelletBody = new RectangleShape();
			pelletBody->setPosition((j * CELLSIZE)+8, (i * CELLSIZE)+8);
			pelletBody->setSize(Vector2f(4, 4));
			pelletBody->setFillColor(Color(255, 183, 174));
			
		}
		pellet(float r, int i, int j) {

			powerPelletBody = new CircleShape();
			ispowerPellet = true;
			powerPelletBody->setPosition((j * CELLSIZE)+4, (i * CELLSIZE)+4);
			powerPelletBody->setFillColor(Color(255, 183, 174));
			powerPelletBody->setRadius(r);
		}
		~pellet() {
		
			if (!ispowerPellet) //Watch out which one is it!
				delete pelletBody;
			else
				delete powerPelletBody;
		}
		union {
			RectangleShape* pelletBody;
			CircleShape* powerPelletBody;
		};

	}pellet;
	unordered_map<string, pellet*> pelletmap;
	static string level;
	float CellSize;
	unsigned int uCellSize;


private:
	void LoadMap();
	void LoadPellets();
};

#endif
