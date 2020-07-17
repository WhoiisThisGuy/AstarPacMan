#include "Inky.h"
#include "Blinky.h"
#include "Scatter.h"
#include "GhostHouse.h"
#include "Pacman.h"

//#include "Chase.h"

Inky::Inky(){

	InkyTexture.loadFromFile(INKYTEXTUREPATH);//Have to do this at every single character... change it

	ghostBody.setSize(Vector2f(GHOSTBODYSIZE, GHOSTBODYSIZE));
	ghostBody.setOrigin(GHOSTBODYSIZE / 2, GHOSTBODYSIZE / 2);
	ghostBody.setPosition(Vector2f((INKYSTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (INKYSTARTY * CELLSIZE) + CELLSIZE / 2));
	//ghostBody.setTexture(&InkyTexture);

	activateTimer = 5.0f;
	active = false;
	firstcomeout = true;
	direction.y = -1;
	rowForAnimation = 2;
	ghostHouseStartNode = {11,18};

	startDirection = { 0,-1 };
	state = new GhostHouse(this);

	
	//targettexture.loadFromFile("Textures/blinkytarget.png");

	//targetMark.setPosition(scatterTargetNode.x * CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	//targetMark.setTexture(&targettexture);
	//targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
}

Inky::~Inky()
{

}

void Inky::Update(const float& dt)
{
	/* update current positions to work with */
	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;
	pacmanTempDirection = Pacman::sTempDirectionOnLevel;
	blinkyTempCoordsOnLevel = Blinky::sTempCoordsOnLevel;

	state->Update(dt); // Update actual state


	//move
	//moveOn(dt);
	
	//targetMark.setPosition((targetNode.x * CELLSIZE) + CELLSIZE / 2, (targetNode.y * CELLSIZE) + CELLSIZE / 2);//Used to show where the target tile is atm

}

//void Inky::Draw(RenderWindow& window)
//{
//	window.draw(ghostBody);
//	//window.draw(targetMark);
//}


void Inky::setTargetNode(Vector2i target)
{
	targetNode = target;
}

void Inky::moveUpAndDown()
{
	//Starts up by default.

	float tempCoords;

	if (direction.y == -1) {
		tempCoords = ((ghostBody.getPosition().y - 10.0f) / CELLSIZE);
		if ((tempCoords) <= 17.50f
			) {
			turnAround();
		}
	}
	else if (direction.y == 1) {
		tempCoords = ((ghostBody.getPosition().y + 10.0f) / CELLSIZE);
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
	ghostBody.setPosition(ghostBody.getPosition());
	if (14.35 > (ghostBody.getPosition().x + 10.0f) / CELLSIZE) {
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

