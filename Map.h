#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#define MAPARRAYSIZEX 10
#define MAPARRAYSIZEY 9
#define CELLSIZE 37.0f

//0 = szabad terület
//1 = block
//7 = PacMan

static int map[MAPARRAYSIZEX][MAPARRAYSIZEY] = {
{ 1,1,1,1,1,1,1,1,1 },
{ 1,0,0,0,0,0,0,0,1 },
{ 1,0,1,0,1,0,1,0,1 },
{ 1,0,1,0,0,0,1,0,1 },
{ 1,0,1,1,1,0,1,0,1 },
{ 1,0,0,0,0,0,0,0,1 },
{ 1,0,1,1,1,0,1,0,1 },
{ 1,0,1,0,0,0,1,0,1 },
{ 1,0,0,0,1,0,0,0,1 },
{ 1,1,1,1,1,1,1,1,1 },
};

class Map
{

public:
	Map();
	void DrawMap(sf::RenderWindow& window);
	void Update(sf::Vector2u PacManPos);

private:
	int MapArray[MAPARRAYSIZEX][MAPARRAYSIZEY];
	float CellSize;
	unsigned int uCellSize;
private:

	sf::Texture tileTexture;
	sf::RectangleShape tile;
	sf::RectangleShape RectMapArr[MAPARRAYSIZEX][MAPARRAYSIZEY];
	void LoadMap(int arr[MAPARRAYSIZEX][MAPARRAYSIZEY]);
	

};

