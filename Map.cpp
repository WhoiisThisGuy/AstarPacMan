#include "Map.h"

int test[MapArraySizeX][MapArraySizeY] = {
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},
	{ 1,1,1,1,1},

};

Map::Map():
	tile(sf::Vector2f(CellSize, CellSize)){
	CellSize = 50.0f;
	uCellSize = static_cast<unsigned int>(CellSize);
	tileTexture.loadFromFile("tiletest.png");
	//tile.setTexture(&tileTexture);
	LoadMap(test);
}



void Map::DrawMap(sf::RenderWindow& window)
{

	for (size_t x = 0; x < MapArraySizeX; x++)
	{
		for (size_t y = 0; y < MapArraySizeY; y++)
		{
			if (MapArray[x][y] == 1) {
				RectMapArr[x][y].setSize(sf::Vector2f(CellSize,CellSize));
				RectMapArr[x][y].setTexture(&tileTexture);
				RectMapArr[x][y].setOutlineThickness(3);
				RectMapArr[x][y].setOutlineColor(sf::Color::Cyan);
				RectMapArr[x][y].setPosition(x* CellSize,y* CellSize);
				window.draw(RectMapArr[x][y]);
			}

		}
	}

}

void Map::LoadMap(int arr[MapArraySizeX][MapArraySizeY])
{

	for (size_t i = 0; i < MapArraySizeX; i++)
	{
		for (size_t j = 0; j < MapArraySizeY; j++)
		{
			MapArray[i][j] = arr[i][j];
		}
	}
}
