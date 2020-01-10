#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

//#define tilesize 60x55
#define MapArraySizeX 24
#define MapArraySizeY 23
#define CellSizeDef 40.0f

class Map
{

public:
	Map();
	void DrawMap(sf::RenderWindow& window);
	void Update(sf::Vector2u PacManPos);

	int getMapArrayValue(int x, int y) const{ return MapArray[x][y]; };

private:
	int MapArray[MapArraySizeX][MapArraySizeY];
	float CellSize;
	unsigned int uCellSize;
private:
	sf::Texture tileTexture;
	sf::RectangleShape tile;
	sf::RectangleShape RectMapArr[MapArraySizeX][MapArraySizeY];
	sf::Vector2u tileSize;
	
	void LoadMap(int arr[MapArraySizeX][MapArraySizeY]);
	
};

