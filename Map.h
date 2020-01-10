#pragma once
#include <SFML\Graphics.hpp>

//#define tilesize 60x55
#define MapArraySizeX 10
#define MapArraySizeY 5

class Map
{

public:
	Map();
	void DrawMap(sf::RenderWindow& window);
	void Update();

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

