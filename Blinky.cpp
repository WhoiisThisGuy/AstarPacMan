#include "Blinky.h"
#include "Scatter.h"
#include "Chase.h"
#include "Pacman.h"

Vector2i Blinky::sTempCoordsOnLevel = { 0 ,0}; //Not accurate...

Blinky::Blinky(){
	BlinkyTexture.loadFromFile(BLINKYTEXTUREPATH);//Have to do this at every single character... change it

	ghostBody.setSize(Vector2f(GHOSTBODYSIZE, GHOSTBODYSIZE));
	ghostBody.setOrigin(GHOSTBODYSIZE / 2, GHOSTBODYSIZE / 2);
	PriorityNumber = 0;
	SetStartState();
	
	ghostHouseStartNode = { 13,18 };
	
	//targetMark.setPosition(scatterTargetNode.x*CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	//targetMark.setTexture(&targettexture);
	//targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
}

Blinky::~Blinky()
{
	std::cout << "Blinky destroyed";
}

void Blinky::Update(const float& dt)
{
	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;

	state->Update(dt);

	//targetMark.setPosition((targetNode.x * CELLSIZE) + CELLSIZE / 2, (targetNode.y * CELLSIZE) + CELLSIZE / 2);//Used to show where the target tile is atm
	
	sTempCoordsOnLevel = getTempCoordsOnLevel(); //For Inky
}

bool Blinky::IsMyGhostIsActive() { return true; }

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

unsigned short int Blinky::GetActivationDotLimit()
{
	return 0;
}

void Blinky::SetStartState()
{
	setState(new Scatter(this));
}

void Blinky::SetStartParams()
{

	rowForAnimation = 0;

	startDirection = { -1,0 };
	active = true;
	direction = startDirection;
	currentState = eScatter;
	animation.selectBox = { 16,16 }; //default 16x16 for ghosts
	animation.uvRect.width = 14;
	animation.uvRect.height = 14;
	animation.firstImage = getDirectionForAnimation();
	animation.imageToSet.x = animation.firstImage;
	animation.imageToSet.y = rowForAnimation;
	animation.Update(0, ANIMATIONSWITCHTIME);
	UpdateTexture();
	//ghostBody.setTexture(&BlinkyTexture);

	firstcomeout = false;

	ghostBody.setPosition(Vector2f((BLINKYSTARTX * CELLSIZE) + CELLSIZE / 2, MAPOFFSET + (BLINKYSTARTY * CELLSIZE) + CELLSIZE / 2));
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
