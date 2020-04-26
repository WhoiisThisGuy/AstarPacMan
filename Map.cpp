#include "Map.h"

string Map::level = "";

Map::Map(){

	CellSize = CELLSIZE;
	uCellSize = static_cast<unsigned int>(CellSize);

	LoadMap();
}
Map::~Map()
{



}

void Map::Update()
{
	
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
	level += "############################";
	level += "#            ##            #";
	level += "# #### ##### ## ##### #### #";
	level += "# #### ##### ## ##### #### #";
	level += "# #### ##### ## ##### #### #";
	level += "#                          #";
	level += "# #### ## ######## ## #### #";
	level += "# #### ## ######## ## #### #";
	level += "#      ##    ##    ##      #";
	level += "###### ##### ## ##### ######";
	level += "###### #####d##d##### ######";
	level += "###### ##          ## ######";
	level += "###### ## ######## ## ######";
	level += "###### ## #      # ## ######";
	level += "######    #      #    ######";
	level += "###### ## #      # ## ######";
	level += "###### ## ######## ## ######";
	level += "###### ##          ## ######";
	level += "###### ## ######## ## ######";
	level += "###### ## ######## ## ######";
	level += "#            ##            #";
	level += "# #### ##### ## ##### #### #";
	level += "# #### #####d##d##### #### #";
	level += "#   ##                ##   #";
	level += "### ## ## ######## ## ## ###";
	level += "### ## ## ######## ## ## ###";
	level += "#      ##    ##    ##      #";
	level += "# ########## ## ########## #";
	level += "# ########## ## ########## #";
	level += "#                          #";
	level += "############################";

}
