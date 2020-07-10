#include "Blinky.h"
#include "Scatter.h"
#include "Chase.h"
#include "Pacman.h"

Vector2i Blinky::sTempCoordsOnLevel = { 0 ,0}; //Not accurate...

Blinky::Blinky(){
	BlinkyTexture.loadFromFile(BLINKYTEXTUREPATH);//Have to do this at every single character... change it

	ghostBody.setSize(Vector2f(GHOSTBODYSIZE, GHOSTBODYSIZE));
	ghostBody.setOrigin(GHOSTBODYSIZE / 2, GHOSTBODYSIZE / 2);
	ghostBody.setPosition(Vector2f((BLINKYSTARTX * CELLSIZE)+ CELLSIZE/2, MAPOFFSET+(BLINKYSTARTY * CELLSIZE)+ CELLSIZE / 2));
	ghostBody.setTexture(&BlinkyTexture);

	firstcomeout = false;
	direction.x = -1;
	
	state = new Scatter(this);
	
	//targettexture.loadFromFile("Textures/blinkytarget.png");


	//targetMark.setPosition(scatterTargetNode.x*CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	//targetMark.setTexture(&targettexture);
	//targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
}

Blinky::~Blinky()
{

}

void Blinky::Update(const float& dt)
{
	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;

	state->Update(dt);
	//moveOn(dt);
	//targetMark.setPosition((targetNode.x * CELLSIZE) + CELLSIZE / 2, (targetNode.y * CELLSIZE) + CELLSIZE / 2);//Used to show where the target tile is atm

	ghostBody.setTextureRect(animation.uvRect);
	
	sTempCoordsOnLevel = getTempCoordsOnLevel(); //For Inky
}

void Blinky::setTargetNode(Vector2i target)
{
	targetNode = target;
}

void Blinky::setChaseTargetNode()
{
	targetNode = pacManTempCoordsOnLevel;
}

void Blinky::setScatterTargetNode()
{
	targetNode = scatterTargetNode;
}

Vector2i Blinky::getTempCoordsOnLevel() const /* Gives back the top left corners coordinates (1,1), (2,1) etc.. */
{
	Vector2i Position;

	Position.x = (int)(ghostBody.getPosition().x / CELLSIZE);
	Position.y = (int)(ghostBody.getPosition().y / CELLSIZE);

	return Position;
}

void Blinky::setStartPositions()
{
	if (state)
		delete state;
	
	ghostBody.setPosition(Vector2f((BLINKYSTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (BLINKYSTARTY * CELLSIZE) + CELLSIZE / 2));
	firstcomeout = false;
	direction.x = -1;

	state = new Scatter(this);
}

//void Blinky::FindPath() Old method
//{
//	int result;// only for debug, DELETE it
//
//	sf::Vector2f temp = Map::getPacmanTempPosition();
//
//	Pair start = std::make_pair((int)(ghostBody.getPosition().y / CELLSIZE), (int)(ghostBody.getPosition().x / CELLSIZE));
//	Pair dest = std::make_pair((int)(temp.y / CELLSIZE), (int)(temp.x / CELLSIZE));
//
//	result = aStarSearch(start, dest, Path);
//}
