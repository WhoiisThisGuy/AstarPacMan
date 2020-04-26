#include "Pinky.h"
#include "Scatter.h"
#include "GhostHouse.h"
#include "Pacman.h"
//#include "Chase.h"

Pinky::Pinky() {

	PinkyTexture.loadFromFile(PINKYTEXTUREPATH);//Have to do this at every single character... change it

	animation = new Animation(PinkyTexture, imageCount);

	pictureBody.setSize(Vector2f(PICTUREBODYSIZE, PICTUREBODYSIZE));
	pictureBody.setOrigin(PICTUREBODYSIZE / 2, PICTUREBODYSIZE / 2);
	pictureBody.setPosition(Vector2f((PINKYSTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (PINKYSTARTY * CELLSIZE) + CELLSIZE / 2));
	pictureBody.setTexture(&PinkyTexture);

	realBody.setSize(Vector2f(REALBODYSIZE, REALBODYSIZE));
	realBody.setOrigin(REALBODYSIZE / 2, REALBODYSIZE / 2);
	realBody.setPosition(pictureBody.getPosition());

	activateTimer = 0.0f;
	active = false;
	limitspeed = true;
	firstcomeout = true;
	direction.y = -1;
	row = 0;
	//pictureBody.setTextureRect(animation->uvRect); //DELETE THIS

	state = new GhostHouse(this);
	targettexture.loadFromFile("Textures/blinkytarget.png");

	targetMark.setPosition(scatterTargetNode.x * CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	targetMark.setTexture(&targettexture);
	targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
}

Pinky::~Pinky()
{

	delete animation;
}

void Pinky::Update(float dt)
{
	pacmanTempDirection = Pacman::sTempCoordsOnLevel;

	state->Update();
	moveOn(dt);
	
	setRow();
	animation->Update(row, dt, ANIMATIONSWITCHTIME);
	pictureBody.setTextureRect(animation->uvRect);

	if (stateToSet) { /* Handling new states here, this is ... wierd? Try change it. */
		delete state;
		state = stateToSet;
		stateToSet = NULL;
	}
	targetMark.setPosition((targetNode.x * CELLSIZE) + CELLSIZE / 2, (targetNode.y * CELLSIZE) + CELLSIZE / 2);//Used to show where the target tile is atm

}

void Pinky::Draw(sf::RenderWindow& window)
{

	window.draw(pictureBody);
	window.draw(targetMark);
	//window.draw(realBody); only for debug DELETE IT
}


void Pinky::setTargetNode(Vector2i target)
{
	targetNode = target;
}

void Pinky::moveUpAndDown()
{
	//Starts up by default.

	realBody.setPosition(pictureBody.getPosition());
	float tempCoords;

	if (direction.y == -1) {
		tempCoords = ((realBody.getPosition().y - 10.0f) / CELLSIZE);
		if ((tempCoords) <= 17.50f
			) {
			turnAround();
		}
	}
	else if (direction.y == 1) {
		tempCoords = ((realBody.getPosition().y + 10.0f) / CELLSIZE);
		if ((tempCoords) >= 19.50f
			) {
			turnAround();
		}
	}

}

bool Pinky::moveToFourteenDotThirtyFive()
{

//She is already at moveToFourteenDotThirtyFive coordinate
	
	return true;
}

void Pinky::setChaseTargetNode()
{
	targetNode = pacManTempCoordsOnLevel;
	//If pacman is facing RIGHT
	if (pacmanTempDirection.x == 1)
		targetNode.x += 4;
	//If pacman is facing DOWN
	else if (pacmanTempDirection.y == 1)
		targetNode.y+= 4;
	//If pacman is facing LEFT
	else if (pacmanTempDirection.x == -1)
		targetNode.x -= 4;
	//If pacman is facing UP
	else if (pacmanTempDirection.y == -1) {
		targetNode.x -= 4;
		targetNode.y -= 4;
	}
	return;
}

void Pinky::setScatterTargetNode()
{
	targetNode = scatterTargetNode;
}
