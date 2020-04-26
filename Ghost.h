#include "Animation.h" //Animation includes the Grahpics.hpp
#include "ActorState.h"
#include "Map.h"


#ifndef H_GHOST
#define H_GHOST

class Ghost
{
	

public:
	virtual ~Ghost();
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void setTargetNode(Vector2i) = 0; //Maybe not needed

	virtual void setChaseTargetNode() = 0;
	virtual void setScatterTargetNode() = 0;
	bool nextNodeReached();
	
	void turnAround();
	void setDirection();
	void calculateNewNextNode();
	//inline bool didIcatchPacman() { //delete this if the v2 version works fine
	//	sf::FloatRect pacmanRect = Map::getPacmanTempGlobalBounds();
	//	sf::FloatRect ghostRect;
	//	ghostRect = ghostBody.getGlobalBounds();

	//	if (ghostRect.intersects(pacmanRect))
	//		return true;

	//	return false;
	//};
	//bool didIcatchPacmanV2();

	void setState(ActorState* pstateToSet) {
		stateToSet = pstateToSet;
	}
	virtual void moveUpAndDown() {}; //really amateur solution to move up and down in the ghost house
	virtual bool moveToFourteenDotThirtyFive() { return true; }; //really amateur solution to get the ghost into the middle of the ghost house
	bool comeOutFromHouse();
	//virtual bool moveDown();
	//virtual void moveOut();
	bool isActive() const { return active; }

public:
	
	bool firstcomeout; //coming out first from the house?
	bool limitspeed; //coming out first from the house?
	
	float activateTimer; //When can the ghost come out from the house
protected:

	/* constants start */
	const int SPEED = 150;
	const int LIMITEDSPEED = 80;
	const float PICTUREBODYSIZE = 40.0f;
	const float REALBODYSIZE = 20.0f;
	const float ANIMATIONSWITCHTIME = 0.50f;
	const Vector2u imageCount = {2,8};
	/* constants end */

	

	RectangleShape pictureBody; //PictureBody
	RectangleShape realBody; //RealBody

	RectangleShape targetMark;

	ActorState* state;
	ActorState* stateToSet; //The tactic is that I am watching if there is a new state to set.

	Vector2i direction;  //temporary direction
	Vector2i targetNode; //final destination
	Vector2i nextNode; //What is the next node to go into
	
	Vector2i pacManTempCoordsOnLevel; //needed for chasing

	int row; //row for animation
	bool active;


protected:

	// Function to calculate distance 
	int eucledianDistance(int x1, int y1, int x2, int y2)
	{
		// Calculating distance 
		return sqrt(pow(x2 - x1, 2) +
			pow(y2 - y1, 2) * 1.0);
	}

	inline sf::Vector2i ghostTempCorrdinate() const {

		sf::Vector2i ghostTempCoord;
		ghostTempCoord.x = (int)(realBody.getPosition().x / CELLSIZE);
		ghostTempCoord.y = (int)(realBody.getPosition().y / CELLSIZE);
		return ghostTempCoord;
	}

	inline void setRow() {
		direction.x == 1 ? row = 0
			: direction.x == -1 ? row = 1
			: direction.y == -1 ? row = 2
			: direction.y == 1 ? row = 3
			: row = 0;
	}


	void moveOn(float& dt);
};

#endif
