#include "Map.h"

Map::Map(){
	CellSize = CELLSIZE;
	tile.setSize(sf::Vector2f(CellSize, CellSize));
	uCellSize = static_cast<unsigned int>(CellSize);
	tileTexture.loadFromFile("tiletest.png");
	LoadMap(map);

	
}

void Map::DrawMap(sf::RenderWindow& window)
{

	for (size_t x = 0; x < MAPARRAYSIZEX; x++)
	{
		for (size_t y = 0; y < MAPARRAYSIZEY; y++)
		{
			if (MapArray[x][y] == 1) {
				window.draw(RectMapArr[x][y]);
			}
			//if (MapArray[x][y] == 7)
			//{
			//	
			//	//window.draw(RectMapArr[x][y]);
			//}

		}
	}

}

//Could create a faster method for this maybe

void Map::Update(sf::Vector2u PacManPos)
{
	for (size_t x = 0; x < MAPARRAYSIZEX; x++)
	{
		for (size_t y = 0; y < MAPARRAYSIZEY; y++)
		{
			//PacMan-t setelni az int arrayba.
			//if (x == PacManPos.x && y == PacManPos.y) {
			//	MapArray[x][y] = 7;
			//}
		}
	}
}

void Map::LoadMap(int arr[MAPARRAYSIZEX][MAPARRAYSIZEY])
{

	for (size_t i = 0; i < MAPARRAYSIZEX; i++)//Másolni a map felépítést.
	{
		for (size_t j = 0; j < MAPARRAYSIZEY; j++)
		{
			MapArray[i][j] = arr[i][j];
			
		}
	}
	
	for (size_t x = 0; x < MAPARRAYSIZEX; x++)
	{
		for (size_t y = 0; y < MAPARRAYSIZEY; y++)
		{
			if (MapArray[x][y] == 1) {
				RectMapArr[x][y].setSize(sf::Vector2f(CellSize, CellSize));
				RectMapArr[x][y].setTexture(&tileTexture);
				/*RectMapArr[x][y].setOutlineThickness(2);
				RectMapArr[x][y].setOutlineColor(sf::Color::Black);*/
				RectMapArr[x][y].setPosition(y * CellSize+1, x * CellSize+1);
			}
		}
	}
}
