#include "Clyde.h"
#include "Scatter.h"
#include "GhostHouse.h"
#include "Pacman.h"

//#include "Chase.h"

Clyde::Clyde() {

	ClydeTexture.loadFromFile(CLYDETEXTUREPATH);//Have to do this at every single character... change it

	ghostBody.setSize(Vector2f(GHOSTBODYSIZE, GHOSTBODYSIZE));
	ghostBody.setOrigin(GHOSTBODYSIZE / 2, GHOSTBODYSIZE / 2);
	ghostBody.setPosition(Vector2f((CLYDESTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (CLYDESTARTY * CELLSIZE) + CELLSIZE / 2));
	//ghostBody.setTexture(&ClydeTexture);

	//Color color(255,183,81);
	//
	//
	//clydeCircle.setRadius(8.0f* CELLSIZE);
	//clydeCircle.setFillColor(Color::Transparent);
	//clydeCircle.setOutlineColor(color);
	//clydeCircle.setOutlineThickness(3.0f);
	//clydeCircle.setOrigin(clydeCircle.getLocalBounds().width/2, clydeCircle.getLocalBounds().height / 2);
	//clydeCircle.setPosition(ghostBody.getPosition());
	ghostHouseStartNode = { 16,18 };
	rowForAnimation = 3;
	activateTimer = 0.0f; //5
	active = false;
	firstcomeout = true;
	direction.y = -1;
	startDirection = { 0,-1 };
	//stateStack.push(new GhostHouse(this));
	
	targettexture.loadFromFile("Textures/blinkytarget.png");

	targetMark.setPosition(scatterTargetNode.x * CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	targetMark.setTexture(&targettexture);
	targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
	state = new GhostHouse(this);
}

Clyde::~Clyde()
{
	std::cout << "Clyde destroyed";
}

void Clyde::Update(const float& dt)
{

	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;
	
	state->Update(dt);
	//moveOn(dt);

	
	//handleState();
	//if (stateToSet) { /* Handling new states here, this is ... wierd? Try change it. */
	//	//delete state;
	//	delete stateStack.top();

	//	stateStack.pop();
	//	stateStack.push(stateToSet);

	//	//state = stateToSet;
	//	stateToSet = NULL;
	//}
	targetMark.setPosition((targetNode.x * CELLSIZE) + CELLSIZE / 2, (targetNode.y * CELLSIZE) + CELLSIZE / 2);//Used to show where the target tile is atm
	clydeCircle.setPosition(ghostBody.getPosition());
}

//void Clyde::Draw(RenderWindow& window)
//{
//
//	window.draw(ghostBody);
//	window.draw(targetMark);
//	//window.draw(clydeCircle);
//	//window.draw(realBody); //only for debug DELETE IT
//}


void Clyde::setTargetNode(Vector2i target)
{
	targetNode = target;
}

void Clyde::moveUpAndDown()
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

bool Clyde::moveToFourteenDotThirtyFive()
{
	if (direction.x != -1) {
		direction.x = -1;
		direction.y = 0;
	}
	ghostBody.setPosition(ghostBody.getPosition());
	if (13.75f < (ghostBody.getPosition().x - 10.0f) / CELLSIZE) {
		return false;
	}

	return true;
}


void Clyde::setChaseTargetNode()
{
	if (manhattanDistance(getTempCoordsOnLevel().x, getTempCoordsOnLevel().y, pacManTempCoordsOnLevel.x, pacManTempCoordsOnLevel.y) <= 8)
		targetNode = scatterTargetNode;
	else
		targetNode = pacManTempCoordsOnLevel;
	return;
}

void Clyde::setScatterTargetNode()
{
	targetNode = scatterTargetNode;
}

Vector2i Clyde::getTempCoordsOnLevel()
{
	Vector2i Position;

	Position.x = (int)(ghostBody.getPosition().x / CELLSIZE);
	Position.y = (int)(ghostBody.getPosition().y / CELLSIZE);

	return Position;
}
