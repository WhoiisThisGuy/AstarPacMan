//#include "Astar.h"
//
//Astar::Astar() {
//
//	
//
//}
//
//void Astar::createPath(node AstarArray[MapArraySizeX][MapArraySizeY], Coordinate goal, Coordinate start)
//{
//
//	int x, y;
//
//	x = y = 0;
//
//	x = goal.x;
//	y = goal.y;
//
//	std::list<Coordinate> Path;
//	Coordinate temp;
//
//	temp.x = x;
//	temp.y = y;
//
//	while (x != start.x || y != start.y) {
//
//		temp.x = x;
//		temp.y = y;
//		Path.push_front(temp);
//		x = AstarArray[temp.x][temp.y].parentX;
//		y = AstarArray[temp.x][temp.y].parentY;
//	}
//	Path.push_front(temp);
//	std::cout << "The Found Path: " << std::endl;
//	while (!Path.empty()) {
//
//		Coordinate temp;
//
//		temp.x = (*Path.begin()).x;
//		temp.y = (*Path.begin()).y;
//
//		std::cout << "x: " << temp.x << " " << "y: " << temp.y << std::endl;
//
//		Path.pop_front();
//	}
//
//}
//
//bool Astar::isFreeCell()
//{
//	
//	return false;
//}
//
//bool Astar::StandardAstar(int MapArray[MapArraySizeX][MapArraySizeY], Coordinate start, Coordinate goal)
//{
//
//	float tempG, tempF, tempH;
//
//	bool closedList[MapArraySizeX][MapArraySizeY];
//
//	memset(closedList,0,sizeof(closedList));
//
//	node AstarMap[MapArraySizeX][MapArraySizeY];
//
//	//std::vector<node> openlist, closedlist;
//	std::list<node> openlist; // vector helyett gyorsabb
//
//	for (size_t x = 0; x < MapArraySizeX; x++)
//	{
//		for (size_t y = 0; y < MapArraySizeY; y++)
//		{
//			AstarMap[x][y].parentX = -1;
//			AstarMap[x][y].parentX = -1;
//			AstarMap[x][y].f = -1;
//			AstarMap[x][y].g = -1;
//			AstarMap[x][y].h = -1;
//		}
//	}
//	node tempNode; // aktualis node
//
//	tempNode.f = tempNode.g = tempNode.h = 0.0;
//	tempNode.parentX = tempNode.parentX = 0;
//	tempNode.posX = start.x; 
//	tempNode.posY = start.y;
//	//Elsõt hozzá adjuk az openlisthez
//	openlist.push_front(tempNode);
//
///*Look for the node which has the lowest
//f on the open list. Refer to this node
//as the current node.
//b. Switch it to the closed list.*/
//
//	while (!openlist.empty())
//	{
//		//p = removefirst(q)
//		//x = lastnode(p)
//
//		lookforsmallestF(openlist,&tempNode); //legkisebbet keresi, és ki is szedjük az openlistrõl
//		//legkisebb f értékût vegyük aktuálisnak
//
//		closedList[tempNode.posX][tempNode.posY] = 1;
//
//		//node Right
//
//		//    [Right]
//		//[][tempnode][]
//		//      []
//		if (closedList[tempNode.posX][tempNode.posY-1] != 1 && MapArray[tempNode.posX][tempNode.posY-1] != 1) {
//
//			if (tempNode.posX == goal.x && tempNode.posY == goal.y - 1) { /////////END
//				//a szomszédos node a cél node, end.
//				AstarMap[tempNode.posX][tempNode.posY - 1].parentX = tempNode.posX;
//				AstarMap[tempNode.posX][tempNode.posY - 1].parentY = tempNode.posY;
//
//			}
//
//			//ha nincs closed listen és nem blokkolt cella.
//			tempG = tempNode.g + 1;
//			tempH = ManHattan(tempNode.posX, tempNode.posY - 1, goal);
//			tempF = tempG + tempH;
//
//			if (AstarMap[tempNode.posX][tempNode.posY - 1].f == -1) {
//				//nincs még az open listen mert nincs f értéke sem, felvesszük
//
//				AstarMap[tempNode.posX][tempNode.posY - 1].g = tempG;
//				AstarMap[tempNode.posX][tempNode.posY - 1].h = tempH;
//				AstarMap[tempNode.posX][tempNode.posY - 1].f = tempF;
//				AstarMap[tempNode.posX][tempNode.posY - 1].parentX = tempNode.posX;
//				AstarMap[tempNode.posX][tempNode.posY - 1].parentY = tempNode.posY;
//			}
//			else if (AstarMap[tempNode.posX][tempNode.posY - 1].f > tempF) {
//				//Ha ez jobb útvonal az Up node-ba akkor rögzítjük
//				AstarMap[tempNode.posX][tempNode.posY - 1].g = tempG;
//				AstarMap[tempNode.posX][tempNode.posY - 1].h = tempH;
//				AstarMap[tempNode.posX][tempNode.posY - 1].f = tempF;
//				AstarMap[tempNode.posX][tempNode.posY - 1].parentX = tempNode.posX;
//				AstarMap[tempNode.posX][tempNode.posY - 1].parentY = tempNode.posY;
//
//				openlist.push_back(AstarMap[tempNode.posX][tempNode.posY - 1]);
//				
//			}
//		}
//
//		//node Down
//
//		//     []
//		//[][tempnode][Down]
//		//      []
//		if (closedList[tempNode.posX+1][tempNode.posY] != 1 && MapArray[tempNode.posX + 1][tempNode.posY] != 1) {
//
//			if (tempNode.posX == goal.x+1 && tempNode.posY == goal.y) { //////END
//				//a szomszédos node a cél node, end.
//				AstarMap[tempNode.posX + 1][tempNode.posY].parentX = tempNode.posX;
//				AstarMap[tempNode.posX + 1][tempNode.posY].parentY = tempNode.posY;
//
//			}
//
//			//ha nincs closed listen és nem blokkolt cella.
//			tempG = tempNode.g + 1;
//			tempH = ManHattan(tempNode.posX + 1, tempNode.posY, goal);
//			tempF = tempG + tempH;
//
//			if (AstarMap[tempNode.posX + 1][tempNode.posY].f == -1) {
//				//nincs még az open listen mert nincs f értéke sem, felvesszük
//
//				AstarMap[tempNode.posX + 1][tempNode.posY].g = tempG;
//				AstarMap[tempNode.posX + 1][tempNode.posY].h = tempH;
//				AstarMap[tempNode.posX + 1][tempNode.posY].f = tempF;
//				AstarMap[tempNode.posX + 1][tempNode.posY].parentX = tempNode.posX;
//				AstarMap[tempNode.posX + 1][tempNode.posY].parentY = tempNode.posY;
//			}
//			else if (AstarMap[tempNode.posX + 1][tempNode.posY].f > tempF) {
//				//Ha ez jobb útvonal az Up node-ba akkor rögzítjük
//				AstarMap[tempNode.posX + 1][tempNode.posY].g = tempG;
//				AstarMap[tempNode.posX + 1][tempNode.posY].h = tempH;
//				AstarMap[tempNode.posX + 1][tempNode.posY].f = tempF;
//				AstarMap[tempNode.posX + 1][tempNode.posY].parentX = tempNode.posX;
//				AstarMap[tempNode.posX + 1][tempNode.posY].parentY = tempNode.posY;
//
//				openlist.push_back(AstarMap[tempNode.posX + 1][tempNode.posY]);
//
//			}
//		}
//
//		//node Down
//
//		//     []
//		//[][tempnode][]
//		//    [Left]
//		if (closedList[tempNode.posX][tempNode.posY + 1] != 1 && MapArray[tempNode.posX][tempNode.posY + 1] != 1) {
//
//			if (tempNode.posX == goal.x && tempNode.posY == goal.y + 1) { ////ENDD
//				//a szomszédos node a cél node, end.
//				AstarMap[tempNode.posX][tempNode.posY + 1].parentX = tempNode.posX;
//				AstarMap[tempNode.posX][tempNode.posY + 1].parentY = tempNode.posY;
//			}
//
//			//ha nincs closed listen és nem blokkolt cella.
//			tempG = tempNode.g + 1;
//			tempH = ManHattan(tempNode.posX, tempNode.posY + 1, goal);
//			tempF = tempG + tempH;
//
//			if (AstarMap[tempNode.posX][tempNode.posY + 1].f == -1) {
//				//nincs még az open listen mert nincs f értéke sem, felvesszük
//
//				AstarMap[tempNode.posX][tempNode.posY + 1].g = tempG;
//				AstarMap[tempNode.posX][tempNode.posY + 1].h = tempH;
//				AstarMap[tempNode.posX][tempNode.posY + 1].f = tempF;
//				AstarMap[tempNode.posX][tempNode.posY + 1].parentX = tempNode.posX;
//				AstarMap[tempNode.posX][tempNode.posY + 1].parentY = tempNode.posY;
//			}
//			else if (AstarMap[tempNode.posX][tempNode.posY + 1].f > tempF) {
//				//Ha ez jobb útvonal az Up node-ba akkor rögzítjük
//				AstarMap[tempNode.posX][tempNode.posY + 1].g = tempG;
//				AstarMap[tempNode.posX][tempNode.posY + 1].h = tempH;
//				AstarMap[tempNode.posX][tempNode.posY + 1].f = tempF;
//				AstarMap[tempNode.posX][tempNode.posY + 1].parentX = tempNode.posX;
//				AstarMap[tempNode.posX][tempNode.posY + 1].parentY = tempNode.posY;
//
//				openlist.push_back(AstarMap[tempNode.posX][tempNode.posY + 1]);
//
//			}
//		}
//
//		//         []
//		//[Up][tempnode][]
//		//         []
//		if (closedList[tempNode.posX - 1][tempNode.posY] != 1 && MapArray[tempNode.posX - 1][tempNode.posY] != 1) {
//
//			if (tempNode.posX == goal.x - 1 && tempNode.posY == goal.y) { ////ENDD
//				//a szomszédos node a cél node, end.
//				AstarMap[tempNode.posX - 1][tempNode.posY].parentX = tempNode.posX;
//				AstarMap[tempNode.posX - 1][tempNode.posY].parentY = tempNode.posY;
//			}
//
//			//ha nincs closed listen és nem blokkolt cella.
//			tempG = tempNode.g + 1;
//			tempH = ManHattan(tempNode.posX - 1, tempNode.posY, goal);
//			tempF = tempG + tempH;
//			if (AstarMap[tempNode.posX - 1][tempNode.posY].f == -1) {
//				//nincs még az open listen mert nincs f értéke sem, felvesszük
//
//				AstarMap[tempNode.posX - 1][tempNode.posY].g = tempG;
//				AstarMap[tempNode.posX - 1][tempNode.posY].h = tempH;
//				AstarMap[tempNode.posX - 1][tempNode.posY].f = tempF;
//				AstarMap[tempNode.posX - 1][tempNode.posY].parentX = tempNode.posX;
//				AstarMap[tempNode.posX - 1][tempNode.posY].parentY = tempNode.posY;
//			}
//			else if (AstarMap[tempNode.posX - 1][tempNode.posY].f > tempF) {
//				//Ha ez jobb útvonal az Up node-ba akkor rögzítjük
//				AstarMap[tempNode.posX - 1][tempNode.posY].g = tempG;
//				AstarMap[tempNode.posX - 1][tempNode.posY].h = tempH;
//				AstarMap[tempNode.posX - 1][tempNode.posY].f = tempF;
//				AstarMap[tempNode.posX - 1][tempNode.posY].parentX = tempNode.posX;
//				AstarMap[tempNode.posX - 1][tempNode.posY].parentY = tempNode.posY;
//
//				openlist.push_back(AstarMap[tempNode.posX + 1][tempNode.posY]);
//
//			}
//		}
//
//	}
//	return false;
//}
//
//void Astar::lookforsmallestF(std::list<node>& openlist,node* tempNode) {
//
//	std::list<node>::iterator it,tempit;
//
//	for (it = openlist.begin(); it != openlist.end(); ++it)
//	{
//		if ((*it).f < (*tempNode).f) {
//			*tempNode = *it;
//			tempit = it;
//		}
//	}
//	openlist.erase(tempit);
//}