#include "Clyde.h"
#include "Scatter.h"
#include "GhostHouse.h"
#include "Pacman.h"

//#include "Chase.h"

Clyde::Clyde() {

	ClydeTexture.loadFromFile(CLYDETEXTUREPATH);//Have to do this at every single character... change it

	animation = new Animation(ClydeTexture, imageCount);

	pictureBody.setSize(Vector2f(PICTUREBODYSIZE, PICTUREBODYSIZE));
	pictureBody.setOrigin(PICTUREBODYSIZE / 2, PICTUREBODYSIZE / 2);
	pictureBody.setPosition(Vector2f((CLYDESTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (CLYDESTARTY * CELLSIZE) + CELLSIZE / 2));
	pictureBody.setTexture(&ClydeTexture);

	realBody.setSize(Vector2f(REALBODYSIZE, REALBODYSIZE));
	realBody.setOrigin(REALBODYSIZE / 2, REALBODYSIZE / 2);
	realBody.setPosition(pictureBody.getPosition());


	Color color(255,183,81);
	
	
	clydeCircle.setRadius(8.0f* CELLSIZE);
	clydeCircle.setFillColor(Color::Transparent);
	clydeCircle.setOutlineColor(color);
	clydeCircle.setOutlineThickness(3.0f);
	clydeCircle.setOrigin(clydeCircle.getLocalBounds().width/2, clydeCircle.getLocalBounds().height / 2);
	clydeCircle.setPosition(pictureBody.getPosition());

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

Clyde::~Clyde()
{

	delete animation;
}

void Clyde::Update(float dt)
{

	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;

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
	clydeCircle.setPosition(pictureBody.getPosition());
}

void Clyde::Draw(sf::RenderWindow& window)
{

	window.draw(pictureBody);
	window.draw(targetMark);
	window.draw(clydeCircle);
	//window.draw(realBody); only for debug DELETE IT
}


void Clyde::setTargetNode(Vector2i target)
{
	targetNode = target;
}

void Clyde::moveUpAndDown()
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

bool Clyde::moveToFourteenDotThirtyFive()
{
	if (direction.x != -1) {
		direction.x = -1;
		direction.y = 0;
	}
	realBody.setPosition(pictureBody.getPosition());
	if (14.35 < (realBody.getPosition().x - 10.0f) / CELLSIZE) {
		return false;
	}

	return true;
}

void Clyde::setChaseTargetNode()
{
	
	if (eucledianDistance(getTempCoordsOnLevel().x, getTempCoordsOnLevel().y, pacManTempCoordsOnLevel.x, pacManTempCoordsOnLevel.y) <= 8)
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
	realBody.setPosition(pictureBody.getPosition());

	Position.x = (int)(realBody.getPosition().x / CELLSIZE);
	Position.y = (int)(realBody.getPosition().y / CELLSIZE);

	return Position;
}
