#include "Pacman.h"
#include <Windows.h>

using std::to_string;

Vector2i Pacman::sTempCoordsOnLevel = { 0 ,0 };
Vector2i Pacman::sTempDirectionOnLevel = { 0 ,0 };
bool Pacman::normalSpeedOn = true;
float Pacman::speed = levelValues[LEVELNUMBER][2];
RectangleShape Pacman::body;

Pacman::Pacman() {

	row = 1;
	havebufferedmove = false;

	tempDirection = STARTDIRECTION;
	bufferedDirection = tempDirection;

	body.setSize(Vector2f(PACMANSIZEX, PACMANSIZEY));
	body.setOrigin(PACMANSIZEX / 2, PACMANSIZEY / 2);
	body.setPosition(Vector2f{ (PACMANSTARTPOSX * CELLSIZE) - 12.0f, (((PACMANSTARTPOSY * CELLSIZE) - 12.0f)) });

	PacmanTexture.loadFromFile(PACMANTEXTUREPATH);//Have to do this at every single character... change it, do not want to use pointers
	animation = new Animation(this);
	body.setTexture(&PacmanTexture);
	

	deathStarted = false;
}

Pacman::~Pacman()
{

	delete animation;
}

void Pacman::Draw(RenderWindow& window)
{

	window.draw(body);

}

bool Pacman::Update(const float& dTime, RenderWindow& window)
{
	if (paused)
		return false;

	if (Game_Over) { /* Catastrophic, over complicated logic. Was too lazy to add another state for pacman */
		if (!deathStarted) { //if death animation did not started yet for pacman, setup and go.
			deathClock.restart().asSeconds();
			animation->AimageCount = Vector2u(12, 1);
			animation->uvRect.width = 16.0f;
			animation->uvRect.height = 14.0f;
			deathStarted = true;
		}
		else if (deathClock.getElapsedTime().asSeconds() > 2) {
			/* animation and return; */
			if (animation->UpdateCustomOfColumns(4, 12, dTime, 0.10f) >= 12) { //12th is the last image of the pacman death animation.
				return true;
			}
			body.setTextureRect(animation->uvRect);
		}
		return false;
	}
	//Not so accurate solution, pollevent should handle events. 
	if (Keyboard::isKeyPressed(Keyboard::Up)) {

		bufferedDirection.y = -1;
		bufferedDirection.x = 0;
		havebufferedmove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		bufferedDirection.y = 1;
		bufferedDirection.x = 0;
		havebufferedmove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {


		bufferedDirection.x = -1;
		bufferedDirection.y = 0;
		havebufferedmove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {

		bufferedDirection.x = 1;
		bufferedDirection.y = 0;

		havebufferedmove = true;
	}

	Vector2i tempCoords = getTempCoordsOnLevel();
	char c = Map::GetTile(tempCoords.x, tempCoords.y);

	if (havebufferedmove && c == 'T' || c == 't' || c == 'O') { //T,t,O are marked positions on the Map. These are the places where changing direction is allowed - except when turning around 180°.
		//In the buffered direction I check that: 
		//1, if the Tile in the buffered direction is blocked
		//2, is pacmans origin in the turning zone. The turning zone is like a little square inside the tile, it helps to tell if pacman can turn, prevents half of pacmans texture turn into the wall. The origin has to be inbetween the lower and upper bound, from all axis.
		Vector2f tempPosition;
		tempPosition = { body.getPosition().x / CELLSIZE, body.getPosition().y / CELLSIZE };

		if (bufferedDirection.x == 1 && Map::GetTile(tempCoords.x + 1, tempCoords.y) != '#' && (tempPosition.x >= tempCoords.x + TURNNZONELOWERBOUND && tempPosition.x <= tempCoords.x + TURNNZONEUPPERBOUND && tempPosition.y >= tempCoords.y + TURNNZONELOWERBOUND && tempPosition.y <= tempCoords.y + TURNNZONEUPPERBOUND)) { //Right
			tempDirection = bufferedDirection;
			row = 0;
		}
		else if (bufferedDirection.y == 1 && Map::GetTile(tempCoords.x, tempCoords.y + 1) != '#' && (tempPosition.x >= tempCoords.x + TURNNZONELOWERBOUND && tempPosition.x <= tempCoords.x + TURNNZONEUPPERBOUND && tempPosition.y >= tempCoords.y + TURNNZONELOWERBOUND && tempPosition.y <= tempCoords.y + TURNNZONEUPPERBOUND)) {
			tempDirection = bufferedDirection;
			row = 3;
		}
		else if (bufferedDirection.x == -1 && Map::GetTile(tempCoords.x - 1, tempCoords.y) != '#' && (tempPosition.x >= tempCoords.x + TURNNZONELOWERBOUND && tempPosition.x <= tempCoords.x + TURNNZONEUPPERBOUND && tempPosition.y >= tempCoords.y + TURNNZONELOWERBOUND && tempPosition.y <= tempCoords.y + TURNNZONEUPPERBOUND)) {
			tempDirection = bufferedDirection;
			row = 1;
		}
		else if (bufferedDirection.y == -1 && Map::GetTile(tempCoords.x, tempCoords.y - 1) != '#' && (tempPosition.x >= tempCoords.x + TURNNZONELOWERBOUND && tempPosition.x <= tempCoords.x + TURNNZONEUPPERBOUND && tempPosition.y >= tempCoords.y + TURNNZONELOWERBOUND && tempPosition.y <= tempCoords.y + TURNNZONEUPPERBOUND)) {
			tempDirection = bufferedDirection;
			row = 2;
		}

	}
	else if (bufferedDirection == (tempDirection * -1)) { /* Turning to the opposite direction is allowed anytime. */
		tempDirection = bufferedDirection;
		row = rowToSetForAnimation();
	}

	if (checkCollision(dTime)) { //if checkcollision is OK then pacman can move

		body.move(Vector2f(speed * dTime * tempDirection.x, speed * dTime * tempDirection.y));
		
		animation->Update(row, dTime, ANIMATIONSWITCHTIME);
		body.setTextureRect(animation->uvRect);
	}

	tunnelTeleport(); //Just change position if pacman is @ the end of the tunnel

	/* Pacman should update his data, so the other Ghosts can work with them trough Game and Map. */

	sTempCoordsOnLevel = getTempCoordsOnLevel();
	sTempDirectionOnLevel = tempDirection;

	return false;
}

Vector2i Pacman::getTempCoordsOnLevel() const/* Gives back the coordinates (1,1), (2,1) etc.. */
{
	Vector2i Position;

	Position.x = (int)(body.getPosition().x / CELLSIZE);
	Position.y = (int)(body.getPosition().y / CELLSIZE);

	return Position;
}

bool Pacman::checkCollision(const float& dTime)
{

	Vector2f moveWith = { speed * dTime * tempDirection.x,speed * dTime * tempDirection.y };
	Vector2f tempPosition = body.getPosition();
	Vector2i nextPosition;

	if (tempDirection.x == 1) {
		moveWith.x += OFFSET;
	}
	else if (tempDirection.y == 1) {
		moveWith.y += OFFSET;
	}
	else if (tempDirection.x == -1) {
		moveWith.x -= OFFSET;
	}
	else if (tempDirection.y == -1) {
		moveWith.y -= OFFSET;
	}

	nextPosition.x = int((tempPosition.x + moveWith.x) / CELLSIZE);
	nextPosition.y = int((tempPosition.y + moveWith.y) / CELLSIZE);

	if (Map::GetTile(nextPosition.x, nextPosition.y) != '#' && Map::GetTile(nextPosition.x, nextPosition.y) != '_')
		return true;
	return false;
}



unsigned short int Pacman::rowToSetForAnimation()
{
	unsigned short int row;

	tempDirection.x == 1 ? row = 0
		: tempDirection.x == -1 ? row = 1
		: tempDirection.y == -1 ? row = 2
		: tempDirection.y == 1 ? row = 3
		: row = 0;

	return row;
}

void Pacman::tunnelTeleport()
{

	if (getTempCoordsOnLevel() == Vector2i{ 0,18 } && tempDirection.x == -1) {
		body.setPosition((27 * CELLSIZE) + 12, (18 * CELLSIZE) + 12);
	}
	else if (getTempCoordsOnLevel() == Vector2i{ 27,18 } && tempDirection.x == 1) {
		body.setPosition((0 * CELLSIZE) + 12, (18 * CELLSIZE) + 12);
	}

}

//Just left it here to see the progress
//Found an easier solution instead of these

//
//bool Pacman::canPacMove(float &dTime) const{ /* Collision detection */
//
//	sf::Vector2u pacNextPosA = { 0,0 }; /* These two vectors define that where the top and bottom - depending on which direction is pacman going -
//									of pacman's tile will be after the movement is added to the current position. */
//	sf::Vector2u pacNextPosB = { 0,0 };
//
//	sf::Vector2f tempPosition = body.getPosition();
//	sf::Vector2u tempCoordinates = getTempCoordsOnLevel();
//
//	sf::Vector2f movement = { sf::Vector2f(speed * dTime * tempDirection.x, speed * dTime * tempDirection.y)};
//
//	movement.x *= tempDirection.x;
//	movement.y *= tempDirection.y;
//
//	/* Decide which direction is pacman going. Then I calculate the position where pacman will be after movement vector is added to the position. */
//
//	if (tempDirection.x == 1) {
//
//		pacNextPosA.x = (unsigned int)(((tempPosition.x+ PACMANSIZEX) + movement.x + OFFSETMOVE) / CELLSIZE); //calculation of the top right corner of the rectangleshape
//		pacNextPosA.y = tempCoordinates.y;
//
//		pacNextPosB.x = pacNextPosA.x;
//		pacNextPosB.y = (unsigned int)(((tempPosition.y + PACMANSIZEY) + movement.y) / CELLSIZE); //calculation of the bottom right corner of the rectangleshape
//		
//	}
//	else if (tempDirection.y == 1) {
//
//		pacNextPosA.x = tempCoordinates.x;
//		pacNextPosA.y = (unsigned int)(((tempPosition.y+PACMANSIZEY + OFFSETMOVE) + movement.y) / CELLSIZE);
//
//		pacNextPosB.x = (unsigned int)((tempPosition.x+PACMANSIZEX ) / CELLSIZE);
//		pacNextPosB.y = pacNextPosA.y;
//	}
//	else if(tempDirection.x == -1){
//
//		pacNextPosA.x = (unsigned int)((tempPosition.x + movement.x - OFFSETMOVE) / CELLSIZE);
//		pacNextPosA.y = tempCoordinates.y;
//
//		pacNextPosB.x = pacNextPosA.x;
//		pacNextPosB.y = (unsigned int)((tempPosition.y + PACMANSIZEY ) / CELLSIZE);
//		
//	}
//	else if(tempDirection.y == -1) {
//		
//		pacNextPosA.x = tempCoordinates.x;
//		pacNextPosA.y = (unsigned int)((tempPosition.y + movement.y - OFFSETMOVE) / CELLSIZE);
//
//		pacNextPosB.x = (unsigned int)((tempPosition.x + PACMANSIZEX )/ CELLSIZE);
//		pacNextPosB.y = pacNextPosA.y;
//	}
//	
//	//if(level[pacNextPosA.y][pacNextPosA.x] != 0 || level[pacNextPosB.y][pacNextPosB.x] != 0){ //Coordinates are switched (y first then x) because moving horizontally means moving between columns in the level matrix and moving vertically means moving trough the rows in the level matrix.
//	//	
//	//	return false;
//	//}
//	return true;
//}

//bool Pacman::canPacBufferedMove() const { /* Using the exact same logic like in the canPacMove() function.
//																 The only difference is that I check more further into the direction Pacman would like to go.
//																 This is to tell for sure that the cell is free or not. */
//
//	sf::Vector2u pacNextPosA = { 0,0 }; 
//	sf::Vector2u pacNextPosB = { 0,0 };
//
//	sf::Vector2f tempPosition = body.getPosition();
//	sf::Vector2u tempCoordinates = getTempCoordsOnLevel();
//
//	if (bufferedDirection.x == 1) {
//
//		pacNextPosA.x = (unsigned int)((tempPosition.x + (PACMANSIZEX + OFFSET)) / CELLSIZE); //calculation of the top right corner of the rectangleshape
//		pacNextPosA.y = tempCoordinates.y;
//
//		pacNextPosB.x = pacNextPosA.x;
//		pacNextPosB.y = (unsigned int)((tempPosition.y + PACMANSIZEY) / CELLSIZE); //calculation of the bottom right corner of the rectangleshape
//
//	}
//	else if (bufferedDirection.y == 1) {
//
//		pacNextPosA.x = tempCoordinates.x;
//		pacNextPosA.y = (unsigned int)((tempPosition.y + (PACMANSIZEY + OFFSET)) / CELLSIZE);
//
//		pacNextPosB.x = (unsigned int)((tempPosition.x + PACMANSIZEX) / CELLSIZE);
//		pacNextPosB.y = pacNextPosA.y;
//	}
//	else if (bufferedDirection.x == -1) {
//
//		pacNextPosA.x = (unsigned int)((tempPosition.x - OFFSET) / CELLSIZE);
//		pacNextPosA.y = tempCoordinates.y;
//
//		pacNextPosB.x = pacNextPosA.x;
//		pacNextPosB.y = (unsigned int)((tempPosition.y + PACMANSIZEY) / CELLSIZE);
//
//	}
//	else if (bufferedDirection.y == -1) {
//
//		pacNextPosA.x = tempCoordinates.x;
//		pacNextPosA.y = (unsigned int)((tempPosition.y - OFFSET) / CELLSIZE);
//
//		pacNextPosB.x = (unsigned int)((tempPosition.x + PACMANSIZEX) / CELLSIZE);
//		pacNextPosB.y = pacNextPosA.y;
//	}
//
//	//if (level[pacNextPosA.y][pacNextPosA.x] != 0 || level[pacNextPosB.y][pacNextPosB.x] != 0) { //
//	//comes from Map.h also the coordinates are switched watch for it, y is first.
//	//	return false;
//	//}
//
//	return true;
//}