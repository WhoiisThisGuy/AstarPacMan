#include "Blinky.h"
#include "Scatter.h"
#include "Pacman.h"
//#include "Chase.h"
Vector2i Blinky::sTempCoordsOnLevel = { 0 ,0}; //Not accurate...

Blinky::Blinky(){
	BlinkyTexture.loadFromFile(BLINKYTEXTUREPATH);//Have to do this at every single character... change it

	animation = new Animation(BlinkyTexture, imageCount);

	pictureBody.setSize(Vector2f(PICTUREBODYSIZE, PICTUREBODYSIZE));
	pictureBody.setOrigin(PICTUREBODYSIZE / 2, PICTUREBODYSIZE / 2);
	pictureBody.setPosition(Vector2f((BLINKYSTARTX * CELLSIZE)+ CELLSIZE/2, MAPOFFSET+(BLINKYSTARTY * CELLSIZE)+ CELLSIZE / 2));
	pictureBody.setTexture(&BlinkyTexture);

	realBody.setSize(Vector2f(REALBODYSIZE, REALBODYSIZE));
	realBody.setOrigin(REALBODYSIZE /2, REALBODYSIZE /2);
	realBody.setPosition(pictureBody.getPosition());

	firstcomeout = false;
	direction.x = 1;
	row = 0;
	state = new Scatter(this);
	
	targettexture.loadFromFile("Textures/blinkytarget.png");


	targetMark.setPosition(scatterTargetNode.x*CELLSIZE, scatterTargetNode.y);//Used to show where the target tile is atm
	targetMark.setTexture(&targettexture);
	targetMark.setSize(Vector2f{ CELLSIZE,CELLSIZE });
}

Blinky::~Blinky()
{

	delete animation;
}

void Blinky::Update(float dt)
{
	pacManTempCoordsOnLevel = Pacman::sTempCoordsOnLevel;
	state->Update();
	moveOn(dt);
	targetMark.setPosition((targetNode.x * CELLSIZE) + CELLSIZE / 2, (targetNode.y * CELLSIZE) + CELLSIZE / 2);//Used to show where the target tile is atm
	setRow();
	animation->Update(row, dt, ANIMATIONSWITCHTIME);
	pictureBody.setTextureRect(animation->uvRect);

	if (stateToSet) {
		delete state;
		state = stateToSet;
		stateToSet = NULL;
	}
	
	sTempCoordsOnLevel = getTempCoordsOnLevel();
}

void Blinky::Draw(sf::RenderWindow& window)
{

	window.draw(pictureBody);
	window.draw(targetMark);

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

	Position.x = (int)(pictureBody.getPosition().x / CELLSIZE);
	Position.y = (int)(pictureBody.getPosition().y / CELLSIZE);

	return Position;
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
