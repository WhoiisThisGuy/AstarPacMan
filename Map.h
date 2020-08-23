#include <SFML\Graphics.hpp>
#include <string>
#include <list>
#include <stack>
#include <queue>
#include "LevelVariables.h"
#include "Fruit.h"

/* I consider Map as the bridge between playing class and the character classes pacman, ghosts etc. There are global variables*/

using namespace sf;
using std::string;
using std::list;
using std::stack;
using std::priority_queue;

#ifndef MAP_H

#define MAP_H

extern bool glob_powerOn; //Defined in Map.cpp, only Map and Scatter, Chase, Frighten mods are using it.

extern bool paused;
extern bool elroy1;
extern bool elroy2;


#define MAPOFFSET 4*24 //Needed this for the start positions of the characters
#define MAPWIDTH 28
#define MAPROWS 34 //not used just to remember
#define MAPCOLUMNS 28 //not used just to remember
#define CELLSIZE 24

class Map
{

public:
	Map();
	~Map();
	void Update();
	void Draw(RenderWindow& window);
	void handlePellets();
	void TurnOnPellets();
	static char GetTile(int x, int y);
	bool checkFruitPacmanCollision();
public:
	static unsigned int score;
	static unsigned short int pauseTime;
	unsigned short int FRUITNUMBER;
	void ClearGhostHousePriorityQueue();
	static unsigned short int* DotCounterForGhosts;
	static Clock ClockSinceLastDotEaten;
	static priority_queue<unsigned short int,std::vector<unsigned short int>, std::greater<unsigned short int>> GhostHousePriority;
private:

	Text scoreText; //for current score

	 /////////////////Simple pellets
	
	
	Fruit fruit;
	unsigned short int fruitsSpawned;

	typedef struct pellet {

	private:
		Vector2i coordinates;

	public:
		bool isActive = false;
		RectangleShape pelletBody;

		pellet() {

			pelletBody.setSize(Vector2f(5, 5));
			pelletBody.setFillColor(Color(255, 183, 174));
			pelletBody.setOrigin(2, 2);

		}

	public:
		void setCoordinates(int x, int y) {
			coordinates = { x,y };
		}
		Vector2i getCoordinates() {
			return coordinates;
		}
	}pellet;

	/////////////////Power pellets

	typedef struct powerPellet {
	private:
		Vector2i coordinates;
	public:
		CircleShape powerPelletBody;
		powerPellet(int x, int y) {

			powerPelletBody.setRadius(8);
			powerPelletBody.setFillColor(Color(255, 183, 174));
			powerPelletBody.setOrigin(4, 4); // radius/2
			powerPelletBody.setPosition((y * CELLSIZE)+4, (x * CELLSIZE)+4 ); //+ 4
			coordinates = {y,x};
		}
	public:
		bool operator == (const powerPellet& s) const { return coordinates.x == s.coordinates.x && coordinates.y == s.coordinates.y; }
		//void setCoordinates(int x, int y) { not needed
		//	coordinates = { x,y };
		//}
		Vector2i getCoordinates() {
			return coordinates;
		}
	}powerPellet;

	static string level;
	float CellSize;
	unsigned int uCellSize;
	
	pellet pelletArray[244];
	list<powerPellet> powerPelletList;

	

private:
	void LoadMap();
	void LoadPellets();
};

#endif