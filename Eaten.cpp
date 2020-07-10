#include "Eaten.h"

Eaten::Eaten(Ghost* ghostToHandle, ghostState& prevState)
{
	
	ghost = ghostToHandle;
	previousState = prevState; //maybe I need this
	Init();
}

void Eaten::Update(const float& dt)
{
	float stateTime = stateClock.getElapsedTime().asSeconds();


	if (ghost->turningPointReached()) {

		ghost->chooseRandomDirection();

	}
	ghost->animation.Update(ghost->rowToSetForAnimation(), dt, ghost->ANIMATIONSWITCHTIME);
	
	ghost->moveOn(dt);

}

void Eaten::Init()
{
	stateClock.restart().asSeconds();
	ghost->currentState = eEaten;
}

void Eaten::Exit(const ghostState& state)
{

	switch (state) {

	case eChase:
		ghost->turnAround();
		ghost->setState(new Chase(ghost));
		break;
	case eScatter:
		ghost->turnAround();
		ghost->setState(new Scatter(ghost));
		break;
	case eFrighten:
		ghost->turnAround();
		ghost->setState(new Frighten(ghost, state));
		break;
	}
}
