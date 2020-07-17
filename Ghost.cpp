
#include "Ghost.h"
#include <list>
#include <cstdlib>

using std::list;

Texture Ghost::ghostTexture;

bool Ghost::collideWithPacman()
{
	sf::Vector2i ghostTempCoord = ghostTempCorrdinate();

	if (pacManTempCoordsOnLevel == ghostTempCoord)
		return true;
	return false;
}

Ghost::Ghost() :animation(this){
	isFrightened = false;
	previousTurningpoint = {0,0};
	visible = true;
	inTunnel = false;
	ghostTexture.loadFromFile("Textures/Ghost.png");
	ghostBody.setTexture(&ghostTexture);
}

Ghost::~Ghost()
{
	if (state)
		delete state;

}

bool Ghost::turningPointReached()
{

	Vector2i tempCoords = ghostTempCorrdinate();
	char c = Map::GetTile(tempCoords.x, tempCoords.y);

	if ((c == 'T' || c == 't' || c == 'O') && previousTurningpoint != tempCoords) { //(previousTurningpoint.x != tempCoords.x || previousTurningpoint.y != tempCoords.y)
	
		Vector2f tempPosition;
		tempPosition = { ghostBody.getPosition().x / CELLSIZE, ghostBody.getPosition().y / CELLSIZE };

		if (tempPosition.x >= tempCoords.x + TURNNZONELOWERBOUND && tempPosition.x <= tempCoords.x + TURNNZONEUPPERBOUND && tempPosition.y >= tempCoords.y + TURNNZONELOWERBOUND && tempPosition.y <= tempCoords.y + TURNNZONEUPPERBOUND) {
			previousTurningpoint = tempCoords;
			return true;
		}

	}
	return false;
}

bool Ghost::tunnelPointReached()
{
	Vector2i tempCoords = ghostTempCorrdinate();
	char c = Map::GetTile(tempCoords.x, tempCoords.y);

	if (c == 's') {
		inTunnel = true;
		return inTunnel;
	}

	return false;
}

void Ghost::calculateNewDirection()
{
	Vector2i tempCoordinates = ghostTempCorrdinate();
	int shortestDistFromTargetNode = 1000, temp;

	//Right
	if (direction.x != -1 && Map::GetTile(tempCoordinates.x + 1, tempCoordinates.y) != '#') {
		shortestDistFromTargetNode = manhattanDistance(tempCoordinates.x + 1, tempCoordinates.y, targetNode.x, targetNode.y);
		directionNode = { tempCoordinates.x + 1, tempCoordinates.y };

	}
	//Down
	if (direction.y != -1 && Map::GetTile(tempCoordinates.x, tempCoordinates.y + 1) != '#' && Map::GetTile(tempCoordinates.x, tempCoordinates.y + 1) != 'd' && Map::GetTile(tempCoordinates.x, tempCoordinates.y + 1) != '_') {
		temp = manhattanDistance(tempCoordinates.x, tempCoordinates.y + 1, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			shortestDistFromTargetNode = temp;
			directionNode = { tempCoordinates.x, tempCoordinates.y+1 };

		}
		
	}
	//Left
	if (direction.x != 1 && Map::GetTile(tempCoordinates.x - 1, tempCoordinates.y) != '#') {
		temp = manhattanDistance(tempCoordinates.x - 1, tempCoordinates.y, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			shortestDistFromTargetNode = temp;
			directionNode = { tempCoordinates.x - 1, tempCoordinates.y };

		}
	}
	//Up
	if (direction.y != 1 && Map::GetTile(tempCoordinates.x, tempCoordinates.y - 1) != '#' && Map::GetTile(tempCoordinates.x, tempCoordinates.y - 1) != 'd') {
		temp = manhattanDistance(tempCoordinates.x, tempCoordinates.y - 1, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			directionNode = { tempCoordinates.x, tempCoordinates.y - 1 };
		}

	}

	setDirection();
}

void Ghost::calculateNewDirectionEatenMode()
{
	Vector2i tempCoordinates = ghostTempCorrdinate();
	unsigned short int shortestDistFromTargetNode = 100, temp;

	//Right
	if (direction.x != -1 && Map::GetTile(tempCoordinates.x + 1, tempCoordinates.y) != '#') {
		shortestDistFromTargetNode = manhattanDistance(tempCoordinates.x + 1, tempCoordinates.y, targetNode.x, targetNode.y);
		directionNode = { tempCoordinates.x + 1, tempCoordinates.y };

	}
	//Down
	if (direction.y != -1 && Map::GetTile(tempCoordinates.x, tempCoordinates.y + 1) != '#') {
		temp = manhattanDistance(tempCoordinates.x, tempCoordinates.y + 1, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			shortestDistFromTargetNode = temp;
			directionNode = { tempCoordinates.x, tempCoordinates.y + 1 };

		}

	}
	//Left
	if (direction.x != 1 && Map::GetTile(tempCoordinates.x - 1, tempCoordinates.y) != '#') {
		temp = manhattanDistance(tempCoordinates.x - 1, tempCoordinates.y, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			shortestDistFromTargetNode = temp;
			directionNode = { tempCoordinates.x - 1, tempCoordinates.y };

		}
	}
	//Up
	if (direction.y != 1 && Map::GetTile(tempCoordinates.x, tempCoordinates.y - 1) != '#') {
		temp = manhattanDistance(tempCoordinates.x, tempCoordinates.y - 1, targetNode.x, targetNode.y);
		if (temp <= shortestDistFromTargetNode) {
			directionNode = { tempCoordinates.x, tempCoordinates.y - 1 };
		}

	}

	setDirection();
}

void Ghost::chooseRandomDirection()
{

	Vector2i tempCoordinates = ghostTempCorrdinate();

	list<Vector2i> possibleDirectionsList = { Vector2i{1,0},Vector2i{0,1},Vector2i{-1,0},Vector2i{0,-1} };

	//Eliminate not allowed directions

	//Right
	if (direction.x == -1 || Map::GetTile(tempCoordinates.x + 1, tempCoordinates.y) == '#' || direction.x == -1 || Map::GetTile(tempCoordinates.x + 1, tempCoordinates.y) == 's') {
		possibleDirectionsList.remove(Vector2i{ 1,0 });
	}
	//Down
	if (direction.y == -1 || Map::GetTile(tempCoordinates.x, tempCoordinates.y + 1) == '#' || Map::GetTile(tempCoordinates.x, tempCoordinates.y + 1) == 'd' || Map::GetTile(tempCoordinates.x, tempCoordinates.y + 1) == '_') {
		possibleDirectionsList.remove(Vector2i{ 0,1 });

	}
	//Left
	if (direction.x == 1 || Map::GetTile(tempCoordinates.x - 1, tempCoordinates.y) == '#' || direction.x == 1 || Map::GetTile(tempCoordinates.x - 1, tempCoordinates.y) == 's') {
		possibleDirectionsList.remove(Vector2i{ -1,0 });
	}
	//Up
	if (direction.y == 1 || Map::GetTile(tempCoordinates.x, tempCoordinates.y - 1) == '#' || Map::GetTile(tempCoordinates.x, tempCoordinates.y - 1) == 'd') {
		possibleDirectionsList.remove(Vector2i{ 0,-1 });
	}

	auto it = possibleDirectionsList.begin();

	advance(it, (rand() % possibleDirectionsList.size()));

	direction = *it;

}

unsigned short int Ghost::getDirectionForAnimation() //Helps to select the column for the ghost
{
	unsigned short int col;

	if (currentState != eEaten) {
		direction.x == 1 ? col = 0
			: direction.x == -1 ? col = 2
			: direction.y == -1 ? col = 4
			: direction.y == 1 ? col = 6
			: col = 0;
	}
	else {

		direction.x == 1 ? col = 8
			: direction.x == -1 ? col = 9
			: direction.y == -1 ? col = 10
			: direction.y == 1 ? col = 11
			: col = 8;

	}

	return col;
}

void Ghost::moveOn(const float& dt)
{

	Vector2f movement = {0.0f,0.0f};

	if (limitspeed) {
		movement.x = LIMITEDSPEED * dt * direction.x;
		movement.y = LIMITEDSPEED * dt * direction.y;
	}
	else {
		movement.x = speed * dt * direction.x;
		movement.y = speed * dt * direction.y;
	}

	ghostBody.move(movement);
	return;
}
bool Ghost::tunnelTeleport()
{
	Vector2i tempCoords = ghostTempCorrdinate();
	char c = Map::GetTile(tempCoords.x, tempCoords.y);

	if (c == 'L' && direction.x == -1) {
		ghostBody.setPosition((27 * CELLSIZE) + 12, (18 * CELLSIZE) + 12);
		return true;
	}
	else if (c == 'R' && direction.x == 1) {
		ghostBody.setPosition((0 * CELLSIZE) + 12, (18 * CELLSIZE) + 12);
		return true;
	}
	return false;
}

void Ghost::UpdateTexture()
{
	ghostBody.setTextureRect(animation.uvRect);
}
void Ghost::turnAround()
{
	direction.x *= -1;
	direction.y *= -1;
	previousTurningpoint = { 0,0 };
}

void Ghost::setDirection() /* sets the coordinate based on the top of the Path */
{

	Vector2i ghostTempCoord = ghostTempCorrdinate();
	Vector2i newDirection;
	
	newDirection.x = ghostTempCoord.x - directionNode.x;
	newDirection.y = ghostTempCoord.y - directionNode.y;

	newDirection.x *= -1;
	newDirection.y *= -1;
	
	direction.x = newDirection.x;
	direction.y = newDirection.y;

	return;
}

void Ghost::setDirection(Vector2i direction_)
{
	direction = direction_;
}

bool Ghost::comeOutFromHouse()
{

	//13 11

	if (direction.y != -1) {
		direction.x = 0;
		direction.y = -1;
	}
	if (15.60f < (ghostBody.getPosition().y) / CELLSIZE) {
		return false;
	}

	//ghostBody.setPosition((14 * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (11 * CELLSIZE) + CELLSIZE / 2);// This is really a wierd solution.
	//ghostBody.setPosition((14 * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (11 * CELLSIZE) + CELLSIZE / 2);//

	active = true;
	direction = {0,0};
	return true;
}

void Ghost::Draw(sf::RenderWindow& window)
{
	if(visible)
		window.draw(ghostBody);
	//window.draw(targetMark);

}

