#include "Inky.h"
#include "Blinky.h"
#include "Scatter.h"
#include "GhostHouse.h"
#include "Pacman.h"

//#include "Chase.h"

Inky::Inky() {

	InkyTexture.loadFromFile(INKYTEXTUREPATH);//Have to do this at every single character... change it

	animation = new Animation(InkyTexture, imageCount);

	pictureBody.setSize(Vector2f(PICTUREBODYSIZE, PICTUREBODYSIZE));
	pictureBody.setOrigin(PICTUREBODYSIZE / 2, PICTUREBODYSIZE / 2);
	pictureBody.setPosition(Vector2f((INKYSTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (INKYSTARTY * CELLSIZE) + CELLSIZE / 2));
	pictureBody.setTexture(&InkyTexture);

	realBody.setSize(Vector2f(REALBODYSIZE, REALBODYSIZE));
	realBody.setOrigin(REALBODYSIZE / 2, REALBODYSIZE / 2);
	realBody.setPosition(pictureBody.getPosition());

	activateTimer = 5.0f;
	active = false;
	limitspeed = true;
	firstcomeout = true;
	direction.y = -1;
	row = 0;
	pictureBody.setTextureRect(animation->uvRect); //DELETE THIS

	state = new GhostHouse(this);
	targettexture.loadFromFile("Textures/blinkytarget.png");

	targetMark.setPosition(scatterTargetNode.x * CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	targetMark.setTexture(&targettexture);
	targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
}

Inky::~Inky()
{

	delete animation;
}

void Inky::Update(float dt)
{

	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;
	pacmanTempDirection = Pacman::sTempDirectionOnLevel;

	blinkyTempCoordsOnLevel = Blinky::sTempCoordsOnLevel;
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

void Inky::Draw(sf::RenderWindow& window)
{

	window.draw(pictureBody);
	window.draw(targetMark);
	//window.draw(realBody); only for debug DELETE IT
}


void Inky::setTargetNode(Vector2i target)
{
	targetNode = target;
}

void Inky::moveUpAndDown()
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

bool Inky::moveToFourteenDotThirtyFive()
{
	if (direction.x != 1) {
		direction.x = 1;
		direction.y = 0;
	}
	realBody.setPosition(pictureBody.getPosition());
	if (14.35 > (realBody.getPosition().x + 10.0f) / CELLSIZE) {
		return false;
	}

	return true;
}

void Inky::setChaseTargetNode()
{

	Vector2i temp;
	Vector2i vectorToBlinky;

	temp = pacManTempCoordsOnLevel;
	//If pacman is facing RIGHT
	if (pacmanTempDirection.x == 1)
		temp.x += 2;
	//If pacman is facing DOWN
	else if (pacmanTempDirection.y == 1)
		temp.y += 2;
	//If pacman is facing LEFT
	else if (pacmanTempDirection.x == -1)
		temp.x -= 2;
	//If pacman is facing UP
	else if (pacmanTempDirection.y == -1) {
		temp.x -= 2;
		temp.y -= 2;
	}

	vectorToBlinky = blinkyTempCoordsOnLevel - temp;

	vectorToBlinky *= -1;

	targetNode = temp + vectorToBlinky;

	return;
}

void Inky::setScatterTargetNode()
{
	targetNode = scatterTargetNode;
}
