#include "Map.h"
#include "Pacman.h"
#include <iostream>

using std::iterator;

string Map::level = "";

bool paused = true;
bool glob_powerOn = false;
bool Game_Over = false;
unsigned short int LEVELNUMBER = 0; //0. is the first level
bool elroy1 = false;
bool elroy2 = false;

Map::Map() {
	
	powerPellet p1(7,1);
	powerPellet p2(7, 26);
	powerPellet p3(27, 1);
	powerPellet p4(27, 26);

	powerPelletList.push_back(p1);
	powerPelletList.push_back(p2);
	powerPelletList.push_back(p3);
	powerPelletList.push_back(p4);

	CellSize = CELLSIZE;
	uCellSize = static_cast<unsigned int>(CellSize);

	LoadMap();
	LoadPellets();
	//texturePowerPellet.loadFromFile("powerpellet.png");
}
Map::~Map()
{

}

void Map::Update()
{

	checkPelletPacmanCollision();
}

void Map::Draw(RenderWindow& window)
{

	for (auto& a : pelletArray)
		if (a.isActive) {
			window.draw(a.pelletBody);
		}
	for (auto& a : powerPelletList)
		window.draw(a.powerPelletBody);
}

void Map::checkPelletPacmanCollision()
{

	Vector2i pelletTempCoords;

	for (auto& a : powerPelletList) {
			
			if (a.getCoordinates() == Pacman::sTempCoordsOnLevel) {
				powerPelletList.remove(a);
				//Setup pacman normal and dot speed
				glob_powerOn = true;
				Pacman::normalSpeedOn = false;
				return;
			}
	}

	for (auto& a : pelletArray) {
		if (a.isActive && a.getCoordinates() == Pacman::sTempCoordsOnLevel) {
			//set up pacman dot speed here
			a.isActive = false;
			Pacman::normalSpeedOn = false;
			return;
		}
	}
	//set up pacman dot speed here
	if (!Pacman::normalSpeedOn) {
		Pacman::normalSpeedOn = true;
		Pacman::speed = levelValues[LEVELNUMBER][1];
		return;
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
	level += "#T....T.....T##T.....T....T#";
	level += "#.####.#####.##.#####.####.#";
	level += "#O####.#####.##.#####.####O#";
	level += "#.####.#####.##.#####.####.#";
	level += "#T....T..T..T..T..T..T....T#";
	level += "#.####.##.########.##.####.#";
	level += "#.####.##.########.##.####.#";
	level += "#T....T##T..T##T..T##T....T#";
	level += "######.#####.##.#####.######";
	level += "######.#####d##d#####.######";
	level += "######.##t  tttt  t##.######";
	level += "######.## ###__### ##.######";
	level += "######.## #      # ##.######";
	level += "L    sT  t#  tt  #t  Ts    R";
	level += "######.## #      # ##.######";
	level += "######.## ######## ##.######";
	level += "######.##t        t##.######";
	level += "######.## ######## ##.######";
	level += "######.## ######## ##.######";
	level += "#T....T..T..T##T..T..T....T#";
	level += "#.####.#####.##.#####.####.#";
	level += "#.####.#####d##d#####.####.#";
	level += "#O.T##T..T..T  T..T..T##T.O#";
	level += "###.##.##.########.##.##.###";
	level += "###.##.##.########.##.##.###";
	level += "#T.T..T##T..T##T..T##T..T.T#";
	level += "#.##########.##.##########.#";
	level += "#.##########.##.##########.#";
	level += "#T..........T..T..........T#";
	level += "############################";

}

void Map::LoadPellets()
{

	//Idea is that I can directly index the level array and here I can set the pelletArray elements directly aswell by using the index variable to help counting.
	//I only increase index if I passed a pellet (power or not).
	//I should get the reversed version of this so I could directly access the actual pellet with pacmans actual coordinates.

	int index = 0;
	for (int i = 5; i < MAPROWS; ++i) {
		for (int j = 1; j < MAPCOLUMNS - 1; ++j) {

			if (level[i * MAPWIDTH + j] == '.' || level[i * MAPWIDTH + j] == 'T') {

				pelletArray[index].pelletBody.setPosition((j * CELLSIZE)+9, (i * CELLSIZE)+9);
				pelletArray[index].setCoordinates(j,i);
				++index;
			}
		}

	}

	//for (int i = 5; i < MAPROWS;++i) {
	//	for (int j = 1; j < MAPCOLUMNS; ++j) {
	//		asd = "";
	//		if (level[i * MAPWIDTH + j] == '.' || level[i * MAPWIDTH + j] == 'T') {
	//				
	//			asd = to_string(j)+"x"+ to_string(i); // The +x is a funny thing... Longstory short, the map datastructure cannot hold the same keys.
	//												//Since I am storing coordinates in strings as keys, the x = 12 + y = 5 coordinates concatenated together is "125", the x = 1 and y = 25 is guess what... "125". Now you get it.
	//												//I had no idea why some pellets just wont appear on the screen. It was a funny moment when I found out this so I leave it here. Should be changed to a better logic later on.
	//			pelletmap.insert({ asd , new pellet(i,j) });

	//		}
	//		else if (level[i * MAPWIDTH + j] == 'O') {
	//			asd = to_string(j)+"x" + to_string(i);
	//			pelletmap.insert({ asd , new pellet(8,i,j) });
	//		}
	//	}

	//}

}
