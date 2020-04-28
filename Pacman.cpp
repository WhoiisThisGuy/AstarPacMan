#include "Pacman.h"
#include <iostream>
#include <Windows.h>

using std::to_string;

Vector2i Pacman::sTempCoordsOnLevel = { 0 ,0};
Vector2i Pacman::sTempDirectionOnLevel = { 0 ,0 };
string Pacman::sTempCoordsOnLevelString = "00";

Pacman::Pacman() {

	speed = PACMANSPEED;
	row = 1;
	havebufferedmove = false;

	tempDirection = STARTDIRECTION;
	bufferedDirection = tempDirection;

	body.setSize(Vector2f(PACMANSIZEX, PACMANSIZEY));
	body.setOrigin(PACMANSIZEX / 2, PACMANSIZEY / 2);
	body.setPosition(Vector2f{ (PACMANSTARTPOSX * CELLSIZE) -12.0f, (((PACMANSTARTPOSY * CELLSIZE)-12.0f )) });

	PacmanTexture.loadFromFile(PACMANTEXTUREPATH);//Have to do this at every single character... change it, do not want to use pointers
	animation = new Animation(PacmanTexture, textureRowNColNumber);
	body.setTexture(&PacmanTexture);

}

Pacman::~Pacman()
{

	delete animation;
}

void Pacman::Draw(RenderWindow& window)
{

	window.draw(body);

}

void Pacman::Update(float dTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Up)) {

		bufferedDirection.y = -1;
		bufferedDirection.x = 0;
		row = 2;
		havebufferedmove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {

		bufferedDirection.y = 1;
		bufferedDirection.x = 0;
		row = 3;
		havebufferedmove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {

		row = 1;
		bufferedDirection.x = -1;
		bufferedDirection.y = 0;
		havebufferedmove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {

		bufferedDirection.x = 1;
		bufferedDirection.y = 0;
		row = 0;
		havebufferedmove = true;
	}
	//tempDirection = bufferedDirection; //DELETE THIS ONLY DEBUG
	if (havebufferedmove && checkBufferedCollision(dTime)) {
		havebufferedmove = false;
		tempDirection = bufferedDirection;
		animation->Update(row, dTime, ANIMATIONSWITCHTIME);
		body.move(Vector2f(speed * dTime * tempDirection.x, speed * dTime * tempDirection.y));
		body.setTextureRect(animation->uvRect);
	}
	else if (checkCollision(dTime)) {
		body.move(Vector2f(speed * dTime * tempDirection.x, speed * dTime * tempDirection.y));
		animation->Update(row, dTime, ANIMATIONSWITCHTIME);
		body.setTextureRect(animation->uvRect);
	}
	sTempCoordsOnLevel = getTempCoordsOnLevel();
	sTempDirectionOnLevel = tempDirection;



	sTempCoordsOnLevelString = "";
	sTempCoordsOnLevelString = to_string(sTempCoordsOnLevel.x)+"x"+ to_string(sTempCoordsOnLevel.y); //see the +x explanation in Map.cpp
//	Ghost::setPacManTempCoordsOnLevel(getTempCoordsOnLevel());
	//else we dont move anywhere
}

Vector2i Pacman::getTempCoordsOnLevel() const/* Gives back the top left corners coordinates (1,1), (2,1) etc.. */
{
	Vector2i Position;

	Position.x = (int)(body.getPosition().x / CELLSIZE);
	Position.y = (int)(body.getPosition().y / CELLSIZE);

	return Position;
}

bool Pacman::checkCollision(float& dTime)
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

	if (Map::GetTile(nextPosition.x, nextPosition.y) != '#')
		return true;
	return false;
}


bool Pacman::checkBufferedCollision(float& dTime)
{

	Vector2f moveWith = { speed * dTime * bufferedDirection.x,speed * dTime * bufferedDirection.y };
	Vector2f tempPosition = body.getPosition();
	Vector2i nextPosition;

	sf::Vector2i tempCoordinates = getTempCoordsOnLevel();

	sf::Vector2i pacNextPosA = { 0,0 }; /* These two vectors define that where the top and bottom - depending on which direction is pacman going -
									of pacman's tile will be after the movement is added to the current position. */
	sf::Vector2i pacNextPosB = { 0,0 };

	if (bufferedDirection.x == 1) {
		moveWith.x += OFFSETB;
	}
	else if (bufferedDirection.y == 1) {
		moveWith.y += OFFSETB;
	}
	else if (bufferedDirection.x == -1) {

		moveWith.x -= OFFSETB;

	}
	else if (bufferedDirection.y == -1) {

		moveWith.y -= OFFSETB;

	}

	nextPosition.x = int((tempPosition.x + moveWith.x) / CELLSIZE);
	nextPosition.y = int((tempPosition.y + moveWith.y) / CELLSIZE);

	if (Map::GetTile(nextPosition.x, nextPosition.y) != '#')
		return true;
	return false;
}

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