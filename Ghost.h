#include "Animation.h" //Animation includes the Grahpics.hpp
//#include "ActorState.h"
#include "Map.h"
#include <stack>

using namespace std;
enum ghostState;
class ActorState;

#ifndef H_GHOST
#define H_GHOST

#define SCORETEXTUREROW 4
#define EYEBALLSTEXTUREROW 1

class Ghost
{
public:
	bool collideWithPacman();
	Ghost();
	virtual ~Ghost();
	virtual void Update(const float&) = 0;
	void Draw(RenderWindow&);
	virtual void setTargetNode(Vector2i) = 0; //Maybe not needed

	virtual void setChaseTargetNode() = 0;
	virtual void setScatterTargetNode() = 0;
	virtual void SetStartState() = 0;
	virtual void SetStartParams() = 0;
	virtual unsigned short int GetActivationDotLimit() = 0; //VISSZAIRNI NULL FUNCTIONRE
	unsigned short int GetGhostPriorityNumber() const{ return PriorityNumber; }
	virtual bool IsMyGhostIsActive() { return *MyGhostIsActive; }

	void setSpeed(float speed_) { speed = speed_; }
	Vector2i getTargetNode() const { return targetNode; }

	/* New movement version */
	bool turningPointReached();
	bool tunnelPointReached(); //Tunnel point is marked with the character 's' on the Map.
	void calculateNewDirection();
	void calculateNewDirectionEatenMode();
	/* ******************** */

	void turnAround();
	void setDirection();
	void setDirection(Vector2i);

	void setState(ActorState* pstateToSet) { //params: 1. The state you want to set
		delete state;
		state = pstateToSet;
	}

	virtual void moveUpAndDown() {}; //really amateur solution to move up and down in the ghost house
	virtual bool moveToFourteenDotThirtyFive() { return true; } //really amateur solution to get the ghost into the middle of the ghost house

	void chooseRandomDirection();

	unsigned short int getDirectionForAnimation();
	bool comeOutFromHouse();
	bool isActive() const { return active; }

	sf::Vector2i ghostTempCorrdinate() const {

		sf::Vector2i ghostTempCoord;
		ghostTempCoord.x = (int)(ghostBody.getPosition().x / CELLSIZE);
		ghostTempCoord.y = (int)(ghostBody.getPosition().y / CELLSIZE);
		return ghostTempCoord;
	}
	void moveOn(const float& dt);
	bool tunnelTeleport();
	void UpdateTexture();
public:
	Vector2i ghostHouseStartNode;
	/* Was too lazy to write get and sets for these. */

	bool firstcomeout; //coming out first from the house?
	bool isFrightened;
	float activateTimer; //When can the ghost come out from the house
	float ANIMATIONSWITCHTIME = 0.25f;
	bool active;
	bool ActivateGhost;
	bool visible;
	bool inTunnel;
	unsigned short int rowForAnimation; //Stores the row for the right colored ghost.
	int speed;
	unsigned short int counterLimit;
	unsigned short int PriorityNumber;
	Vector2i startDirection;

	ghostState currentState;
	Animation animation;
	static Texture ghostTexture;
	bool* MyGhostIsActive;
protected:
	/* constants start */
	const float GHOSTBODYSIZE = 40.0f;
	const float TURNNZONELOWERBOUND = 0.40f;
	const float TURNNZONEUPPERBOUND = 0.60f;
	const Vector2u imageCount = {2,8};
	
	/* constants end */
	

	RectangleShape ghostBody; //ghostBody

	RectangleShape targetMark;

	ActorState* state;

	stack<Vector2i> path;

	Vector2i direction;  //temporary direction
	Vector2i targetNode; //final destination
	Vector2i directionNode; //What is the next node to go into
	
	Vector2i pacManTempCoordsOnLevel; //needed for chasing


protected:

	int manhattanDistance(int x1, int y1, int x2, int y2)
	{
		// Calculating distance 
		return abs(x2 - x1) +
			abs(y2 - y1);
	}
	
	float eucledianDistance(int x1, int y1, int x2, int y2) {
		return sqrt(pow((x2-x1),2) + pow((y2 - y1), 2));
	}


private:
	Vector2i previousTurningpoint;

};



#endif
