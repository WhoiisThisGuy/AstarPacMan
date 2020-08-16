#include "Pinky.h"
#include "Scatter.h"
#include "GhostHouse.h"
#include "Pacman.h"
//#include "Chase.h"

Pinky::Pinky() {

	PinkyTexture.loadFromFile(PINKYTEXTUREPATH);

	ghostBody.setSize(Vector2f(GHOSTBODYSIZE, GHOSTBODYSIZE));
	ghostBody.setOrigin(GHOSTBODYSIZE / 2, GHOSTBODYSIZE / 2);
	ghostBody.setPosition(Vector2f((PINKYSTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (PINKYSTARTY * CELLSIZE) + CELLSIZE / 2));
	//ghostBody.setTexture(&PinkyTexture);

	activateTimer = 0.0f;
	active = false;
	firstcomeout = true;
	//direction.y = -1;
	rowForAnimation = 1;
	ghostHouseStartNode = { 13,18 };

	startDirection = { 0,-1 };
	state = new GhostHouse(this);
	//targettexture.loadFromFile("Textures/blinkytarget.png");
	
	//targetMark.setPosition(scatterTargetNode.x * CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	//targetMark.setTexture(&targettexture);
	//targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
}

Pinky::~Pinky()
{
	std::cout << "Pinky destroyed";
}

void Pinky::Update(const float& dt)
{
	pacmanTempDirection = Pacman::sTempDirectionOnLevel;
	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;

	state->Update(dt);

	//handleState();
	//if (stateToSet) { /* Handling new states here, this is ... wierd? Try change it. */
	//	delete state;
	//	state = stateToSet;
	//	stateToSet = NULL;
	//}
	//targetMark.setPosition((targetNode.x * CELLSIZE) + CELLSIZE / 2, (targetNode.y * CELLSIZE) + CELLSIZE / 2);//Used to show where the target tile is atm

}

//void Pinky::Draw(RenderWindow& window)
//{
//
//	window.draw(ghostBody);
//	//window.draw(targetMark);
//	
//}


void Pinky::setTargetNode(Vector2i target)
{
	targetNode = target;
}

void Pinky::moveUpAndDown()
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

