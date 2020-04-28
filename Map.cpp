#include "Map.h"
#include "Pacman.h"
#include <iostream>

using std::iterator;

string Map::level = "";

bool glob_powerOn = false;

Map::Map(){

	CellSize = CELLSIZE;
	uCellSize = static_cast<unsigned int>(CellSize);

	LoadMap();
	LoadPellets();

	//texturePowerPellet.loadFromFile("powerpellet.png");
}
Map::~Map()
{

	for (auto it = pelletmap.begin(); it != pelletmap.end(); ++it) {
		delete it->second;
	}

}

void Map::Update()
{

	auto it = pelletmap.find(Pacman::sTempCoordsOnLevelString);
	if (it != pelletmap.end()) {
		delete(it->second);
		pelletmap.erase(it);
	}
}

void Map::Draw(RenderWindow& window)
{

	for (auto p : pelletmap) {
		if(!(p.second->ispowerPellet))
			window.draw(*(p.second->pelletBody));
		else
			window.draw(*(p.second->powerPelletBody));
	}
}

char Map::GetTile(int x, int y)
{
	return level[y * MAPWIDTH + x];
}

void Map::LoadMap()
{
	//35*28
	level += "############################"; //Define as big off set as the plus rows, see in the Map.h
	level += "############################"; // plus row
	level += "############################"; // plus row
	level += "############################"; // plus row
	level += "############################"; // change the position se instead of these plus rows
	level += "#............##............#";
	level += "#.####.#####.##.#####.####.#";
	level += "#O####.#####.##.#####.####O#";
	level += "#.####.#####.##.#####.####.#";
	level += "#..........................#";
	level += "#.####.##.########.##.####.#";
	level += "#.####.##.########.##.####.#";
	level += "#......##....##....##......#";
	level += "######.#####.##.#####.######";
	level += "######.#####d##d#####.######";
	level += "######.##          ##.######";
	level += "######.## ######## ##.######";
	level += "######.## #      # ##.######";
	level += "######.   #      #   .######";
	level += "######.## #      # ##.######";
	level += "######.## ######## ##.######";
	level += "######.##          ##.######";
	level += "######.## ######## ##.######";
	level += "######.## ######## ##.######";
	level += "#............##............#";
	level += "#.####.#####.##.#####.####.#";
	level += "#.####.#####d##d#####.####.#";
	level += "#O..##................##..O#";
	level += "###.##.##.########.##.##.###";
	level += "###.##.##.########.##.##.###";
	level += "#......##....##....##......#";
	level += "#.##########.##.##########.#";
	level += "#.##########.##.##########.#";
	level += "#..........................#";
	level += "############################";

}

void Map::LoadPellets()
{
	
	pellet* temp;

	string asd;

	for (int i = 5; i < MAPROWS;++i) {
		for (int j = 1; j < MAPCOLUMNS; ++j) {
			asd = "";
			if (level[i * MAPWIDTH + j] == '.') {
					
				asd = to_string(j)+"x"+ to_string(i); // The +x is a funny story here. Longstory short, the map datastructure wont hold the same keys.
													//Since I am storing coordinates in strings as keys, the x = 12 + y = 5 coordinates in the string is "125", the x = 1 and y = 25 is guess what... "125". Now you get it.
													//I had no idea why some pellets just wont appear on the screen. It was a... funny moment when I found out this so I leave it here.
				pelletmap.insert({ asd , new pellet(i,j) });

			}
			else if (level[i * MAPWIDTH + j] == 'O') {
				asd = to_string(j)+"x" + to_string(i);
				pelletmap.insert({ asd , new pellet(8,i,j) });
			}
		}

	}

}
