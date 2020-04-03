#include "Pacman.h"
#include <iostream>
#include <Windows.h>


Pacman::Pacman(sf::Texture* PacmanTexture, sf::Vector2u imageCount)
	: animation(PacmanTexture, imageCount)
{
	speed = PACMANSPEED;
	row = 1;

	tempDirection = { STARTDIRECTION };
	bufferedDirection = tempDirection ;

	body.setSize(sf::Vector2f(PACMANSIZEX, PACMANSIZEY));
	body.setPosition(STARTPOSX * CELLSIZE, STARTPOSY * CELLSIZE);

	body.setTexture(PacmanTexture);

}

void Pacman::Draw(sf::RenderWindow& window)
{

	window.draw(body);

}

void Pacman::Update(float dTime, sf::RenderWindow& window)
{
	sf::Vector2f movement(0.0f, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			
			bufferedDirection.y = -1;
			bufferedDirection.x = 0;
			row = 2;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			
			bufferedDirection.y = 1;
			bufferedDirection.x = 0;
			row = 3;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			
			row = 1;
			bufferedDirection.x = -1;
			bufferedDirection.y = 0;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			
			bufferedDirection.x = 1;
			bufferedDirection.y = 0;
			row = 0;
			
		}
	movement.x = speed * dTime;
	movement.y = speed * dTime;
	animation.Update(row, dTime, 0.10f);
	body.setTextureRect(animation.uvRect);
	
	/* The logic implemented here is:
	If the entered direction differs from the temporary direction then check if we can move into that direction else try move to the temporary direction,
	if that is not possible then stop moving. */

	if (tempDirection != bufferedDirection && canPacBufferedMove(bufferedDirection)) {
		tempDirection = bufferedDirection;
	}
	else if (!canPacMove(movement, tempDirection)) {
		tempDirection.x = 0;
		tempDirection.y = 0;
	}

	movement.x *= tempDirection.x;
	movement.y *= tempDirection.y;

	body.move(movement);
}

sf::Vector2u Pacman::getUPosition() const
{
	sf::Vector2u Position;

	Position.x = static_cast<unsigned int> (body.getPosition().x / CELLSIZE);
	Position.y = static_cast<unsigned int>(body.getPosition().y / CELLSIZE);

	return Position;
}

bool Pacman::canPacMove(sf::Vector2f movement,sf::Vector2i& Direction) const{ /* Collision detection */

	sf::Vector2u pacNextPosA = { 0,0 }; /* These two vectors define that where the top and bottom - depending on which direction is pacman going -
									of pacman's tile will be after the movement is added to the current position. */
	sf::Vector2u pacNextPosB = { 0,0 };

	sf::Vector2f tempPosition = body.getPosition();
	sf::Vector2f tempCoordinates = body.getPosition()/CELLSIZE;

	movement.x *= Direction.x;
	movement.y *= Direction.y;

	/* Decide which direction is pacman going. Then I calculate the position where pacman will be after movement vector is added to the position. */

	if (Direction.x == 1) {

		pacNextPosA.x = (unsigned int)(((tempPosition.x+ PACMANSIZEX) + movement.x) / CELLSIZE); //calculation of the top right corner of the rectangleshape
		pacNextPosA.y = tempCoordinates.y;

		pacNextPosB.x = pacNextPosA.x;
		pacNextPosB.y = (unsigned int)(((tempPosition.y + PACMANSIZEY) + movement.y) / CELLSIZE); //calculation of the bottom right corner of the rectangleshape
		
	}
	else if (Direction.y == 1) {

		pacNextPosA.x = tempCoordinates.x;
		pacNextPosA.y = (unsigned int)(((tempPosition.y+PACMANSIZEY ) + movement.y) / CELLSIZE);

		pacNextPosB.x = (unsigned int)((tempPosition.x+PACMANSIZEX ) / CELLSIZE);
		pacNextPosB.y = pacNextPosA.y;
	}
	else if(Direction.x == -1){

		pacNextPosA.x = (unsigned int)((tempPosition.x + movement.x) / CELLSIZE);
		pacNextPosA.y = tempCoordinates.y;

		pacNextPosB.x = pacNextPosA.x;
		pacNextPosB.y = (unsigned int)((tempPosition.y + PACMANSIZEY ) / CELLSIZE);
		
	}
	else if(Direction.y == -1) {
		
		pacNextPosA.x = tempCoordinates.x;
		pacNextPosA.y = (unsigned int)((tempPosition.y + movement.y) / CELLSIZE);

		pacNextPosB.x = (unsigned int)((tempPosition.x + PACMANSIZEX )/ CELLSIZE);
		pacNextPosB.y = pacNextPosA.y;
	}
	
	if(map[pacNextPosA.y][pacNextPosA.x] == 1 || map[pacNextPosB.y][pacNextPosB.x] == 1){ //Coordinates are switched (y first then x) because moving horizontally means moving between columns in the map matrix and moving vertically means moving trough the rows in the map matrix.
		
		return false;
	}
	return true;
}


bool Pacman::canPacBufferedMove(sf::Vector2i& Direction) const { /* Using the exact same logic like in the canPacMove() function.
																 The only difference is that I check more further into the direction Pacman would like to go.
																 This is to tell for sure that the cell is free or not. */

	sf::Vector2u pacNextPosA = { 0,0 }; 
	sf::Vector2u pacNextPosB = { 0,0 };

	sf::Vector2f tempPosition = body.getPosition();
	sf::Vector2f tempCoordinates = body.getPosition() / CELLSIZE;

	if (Direction.x == 1) {

		pacNextPosA.x = (unsigned int)((tempPosition.x + (PACMANSIZEX + OFFSET)) / CELLSIZE); //calculation of the top right corner of the rectangleshape
		pacNextPosA.y = tempCoordinates.y;

		pacNextPosB.x = pacNextPosA.x;
		pacNextPosB.y = (unsigned int)((tempPosition.y + PACMANSIZEY) / CELLSIZE); //calculation of the bottom right corner of the rectangleshape

	}
	else if (Direction.y == 1) {

		pacNextPosA.x = tempCoordinates.x;
		pacNextPosA.y = (unsigned int)((tempPosition.y + (PACMANSIZEY + OFFSET)) / CELLSIZE);

		pacNextPosB.x = (unsigned int)((tempPosition.x + PACMANSIZEX) / CELLSIZE);
		pacNextPosB.y = pacNextPosA.y;
	}
	else if (Direction.x == -1) {

		pacNextPosA.x = (unsigned int)((tempPosition.x - OFFSET) / CELLSIZE);
		pacNextPosA.y = tempCoordinates.y;

		pacNextPosB.x = pacNextPosA.x;
		pacNextPosB.y = (unsigned int)((tempPosition.y + PACMANSIZEY) / CELLSIZE);

	}
	else if (Direction.y == -1) {

		pacNextPosA.x = tempCoordinates.x;
		pacNextPosA.y = (unsigned int)((tempPosition.y - OFFSET) / CELLSIZE);

		pacNextPosB.x = (unsigned int)((tempPosition.x + PACMANSIZEX) / CELLSIZE);
		pacNextPosB.y = pacNextPosA.y;
	}

	if (map[pacNextPosA.y][pacNextPosA.x] == 1 || map[pacNextPosB.y][pacNextPosB.x] == 1) { //map comes from Map.h also the coordinates are switched watch for it, y is first.
		return false;
	}

	return true;
}