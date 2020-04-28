#include "Ghost.h"

//bool Ghost::didIcatchPacmanV2() /* I will check if the coordinate of the top left OR the bottom right corner of pacmans tile is in the same cell as the actual ghost is.
//								if yes, then unfortunatley pacman has been caught else the game goes on. */
//{
//	sf::Vector2u ghostTempCoord = ghostTempCorrdinate();
//
//	sf::Vector2f pacmantempPosition = Map::getPacmanTempPosition();
//
//	sf::Vector2u pacmanTopLeft = { (unsigned int)(pacmantempPosition.y / CELLSIZE), (unsigned int)(pacmantempPosition.x / CELLSIZE) };
//	sf::Vector2u pacmanBottomRight = { (unsigned int)((pacmantempPosition.y+PACMANSIZEX) / CELLSIZE), (unsigned int)((pacmantempPosition.x+PACMANSIZEY) / CELLSIZE) };
//
//
//	if (pacmanTopLeft == ghostTempCoord || pacmanBottomRight == ghostTempCoord)
//		return true;
//	return false;
//}

Ghost::Ghost() {
	stateToSet = NULL;
}

Ghost::~Ghost()
{
	if (state)
		delete state;

}

bool Ghost::nextNodeReached()
{

	realBody.setPosition(pictureBody.getPosition());

	Vector2u ghostRealTopLeft = { (unsigned int)((realBody.getPosition().x - realBody.getOrigin().x) / CELLSIZE), (unsigned int)((realBody.getPosition().y - realBody.getOrigin().y) / CELLSIZE) };
	Vector2u ghostRealBottomRight = { (unsigned int)((realBody.getPosition().x + realBody.getOrigin().x) / CELLSIZE), (unsigned int)((realBody.getPosition().y+realBody.getOrigin().y) / CELLSIZE) };

	if (
		nextNode.x == ghostRealTopLeft.x
		&& nextNode.y == ghostRealTopLeft.y
		&& nextNode.x == ghostRealBottomRight.x
		&& nextNode.y == ghostRealBottomRight.y
		) {
		return true;
	}
	return false;
}

void Ghost::moveOn(float& dt)
{

	Vector2f movement = {0.0f,0.0f};

	if (limitspeed) {
		movement.x = (LIMITEDSPEED) * dt * direction.x;
		movement.y = (LIMITEDSPEED) * dt * direction.y;
	}
	else {
		movement.x = SPEED * dt * direction.x;
		movement.y = SPEED * dt * direction.y;
	}

	pictureBody.move(movement);
	return;
}

void Ghost::turnAround()
{

	direction.x *= -1;
	direction.y *= -1;

}

void Ghost::setDirection() /* sets the coordinate based on the top of the Path */
{

	Vector2i ghostTempCoord = ghostTempCorrdinate();
	Vector2i newDirection;
	
	newDirection.x = ghostTempCoord.x - nextNode.x;
	newDirection.y = ghostTempCoord.y - nextNode.y;

	newDirection.x *= -1;
	newDirection.y *= -1;
	
	direction.x = newDirection.x;
	direction.y = newDirection.y;

	return;
}

void Ghost::calculateNewNextNode() //The ghost is not allowed to go opposite direction, and check if the node is empty
{

	Vector2i tempCoordinates = ghostTempCorrdinate();
	int shortestDistFromTargetNode = 1000, temp;

	//Right
	if (direction.x != -1 && Map::GetTile(tempCoordinates.x+1, tempCoordinates.y) != '#') {
		temp = eucledianDistance(tempCoordinates.x+1, tempCoordinates.y, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			shortestDistFromTargetNode = temp;
			nextNode = { tempCoordinates.x+1, tempCoordinates.y };
		}
	}
	//Down
	if (direction.y != -1 && Map::GetTile(tempCoordinates.x, tempCoordinates.y+1 ) != '#') {
		temp = eucledianDistance(tempCoordinates.x, tempCoordinates.y+1, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			shortestDistFromTargetNode = temp;
			nextNode = { tempCoordinates.x, tempCoordinates.y+1 };
		}
	}
	//Left
	if (direction.x != 1 && Map::GetTile(tempCoordinates.x-1, tempCoordinates.y) != '#') {
		temp = eucledianDistance(tempCoordinates.x-1, tempCoordinates.y, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			shortestDistFromTargetNode = temp;
			nextNode = {tempCoordinates.x-1, tempCoordinates.y };
		}
	}
	//Up
	if (direction.y != 1 && Map::GetTile(tempCoordinates.x, tempCoordinates.y-1) != '#' && Map::GetTile(tempCoordinates.x, tempCoordinates.y - 1) != 'd') {
		temp = eucledianDistance(tempCoordinates.x, tempCoordinates.y-1 , targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			nextNode = { tempCoordinates.x, tempCoordinates.y-1 };
		}
			
	}
	
	return;
}

bool Ghost::comeOutFromHouse()
{

	//13 11

	if (direction.y != -1) {
		direction.x = 0;
		direction.y = -1;
	}
	realBody.setPosition(pictureBody.getPosition());
	if (15.0f < (realBody.getPosition().y - 10.0f) / CELLSIZE) {
		return false;
	}

	realBody.setPosition((14 * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (11 * CELLSIZE) + CELLSIZE / 2);// This is really a wierd solution.
	pictureBody.setPosition((14 * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (11 * CELLSIZE) + CELLSIZE / 2);//

	active = true;

	return true;
}



