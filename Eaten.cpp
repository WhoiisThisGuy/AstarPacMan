#include "Eaten.h"
#include "Chase.h"
#include "Scatter.h"
#include "GhostHouse.h"

Eaten::Eaten(Ghost* ghostToHandle,const ghostState& prevState,const unsigned short int& eatenNum_)
{
	ghost = ghostToHandle;
	previousState = prevState; //maybe I need this later
	ghost->animation.imageToSet.x = eatenNum_;
	Init();
}

void Eaten::Update(const float& dt)
{
	float stateTime = stateClock.getElapsedTime().asSeconds();

	if (ghost->ghostTempCorrdinate() == ghost->getTargetNode()) {
		ghost->setTargetNode(ghost->ghostHouseStartNode);
		//return;
	}
	if (ghost->ghostTempCorrdinate() == ghost->ghostHouseStartNode) {
		Exit(eGhostHouse);
		return;
	}

	if (ghost->turningPointReached()) {

		ghost->calculateNewDirectionEatenMode();
		ghost->animation.imageToSet.x = ghost->getDirectionForAnimation();
	}
	ghost->animation.UpdateSingleImage();
	ghost->UpdateTexture();
	ghost->moveOn(dt);

}

void Eaten::Init()
{

	ghost->currentState = eEaten;
	ghost->setSpeed(200); //Eyes move faster
	ghost->animation.imageToSet.y = EYEBALLSTEXTUREROW; //For the animation
	ghost->animation.imageToSet.x = ghost->getDirectionForAnimation(); //get direction immediatley
	//ghost->setTargetNode(Vector2i(13, 19));
	ghost->setTargetNode(Vector2i{ 13,18 });
	stateClock.restart().asSeconds();
	
}

void Eaten::Exit(const ghostState& state)
{

	ghost->setSpeed(150); //Back to normal speed

	switch (state) {

	case eGhostHouse:
		
		ghost->setState(new GhostHouse(ghost));
		break;
	
	}
}
