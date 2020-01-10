#include "Map.h"

//0 = szabad terület
//1 = block
//7 = PacMan

int test[MapArraySizeX][MapArraySizeY] = {
	{ 0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{ 0,0,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1},
	{ 0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
	{ 0,0,0,0,0,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
	{ 1,1,1,1,1,1,1,0,1,1,0,0,0,1,0,0,0,1,0,1,0,1},
	{ 1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1,0,1},
	{ 1,0,1,0,1,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1},
	{ 1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{ 1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,1,1},
	{ 1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1},
	{ 1,0,1,1,1,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1},
	{ 1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1},
	{ 1,0,1,0,1,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1},
	{ 1,0,1,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,1},
	{ 1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,1,1,0,1},
	{ 1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,0,0,0,1,0,1},
	{ 1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,0,1},
	{ 1,1,1,1,1,1,1,0,1,1,0,0,0,1,0,1,1,1,0,1,1,1},
	{ 0,0,0,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1},
	{ 0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,1,0,1},
	{ 0,0,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1},
	{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{ 0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Map::Map():
	tile(sf::Vector2f(CellSize, CellSize)){
	CellSize = CellSizeDef;
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
				window.draw(RectMapArr[x][y]);
			}
			if (MapArray[x][y] == 7)
			{
				window.draw(RectMapArr[x][y]);
			}

		}
	}

}

void Map::Update(sf::Vector2u PacManPos)
{
	for (size_t x = 0; x < MapArraySizeX; x++)
	{
		for (size_t y = 0; y < MapArraySizeY; y++)
		{
			/*if (MapArray[x][y] == 1) {
				RectMapArr[x][y].setSize(sf::Vector2f(CellSize, CellSize));
				RectMapArr[x][y].setTexture(&tileTexture);
				RectMapArr[x][y].setOutlineThickness(3);
				RectMapArr[x][y].setOutlineColor(sf::Color::Black);
				RectMapArr[x][y].setPosition(x * CellSize, y * CellSize);
			}*/
			//PacMan-t setelni az int arrayba.
			if (x == PacManPos.x && y == PacManPos.y) {
				//std::cout << "IN IF";
				MapArray[x][y] = 7;
				RectMapArr[x][y].setFillColor(sf::Color::Magenta);
				RectMapArr[x][y].setPosition(x * CellSize, y * CellSize);
				RectMapArr[x][y].setSize(sf::Vector2f(CellSize, CellSize));
			}
			else if (MapArray[x][y] != 1) {
			
				MapArray[x][y] = 0;
				RectMapArr[x][y].setFillColor(sf::Color::Black);
				RectMapArr[x][y].setPosition(x * CellSize, y * CellSize);
				RectMapArr[x][y].setSize(sf::Vector2f(CellSize, CellSize));
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
			/*if (MapArray[i][j] == 1) {
				std::cout << "x: " << i << "y: " << j<<std::endl;
			}*/

			
		}
	}
	//Másolni a map felépítést.
	for (size_t x = 0; x < MapArraySizeX; x++)
	{
		for (size_t y = 0; y < MapArraySizeY; y++)
		{
			if (MapArray[x][y] == 1) {
				RectMapArr[x][y].setSize(sf::Vector2f(CellSize, CellSize));
				RectMapArr[x][y].setTexture(&tileTexture);
				RectMapArr[x][y].setOutlineThickness(3);
				RectMapArr[x][y].setOutlineColor(sf::Color::Black);
				RectMapArr[x][y].setPosition(x * CellSize, y * CellSize);
			}
		}
	}
}
