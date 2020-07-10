#include "Frighten.h"
#include "Scatter.h"
#include "Chase.h"

Frighten::Frighten(Ghost* ghostToHandle, ghostState prevState) {
	
	ghost = ghostToHandle;
	previousState = prevState;
	//std::cout << "SCATTER\n";
	
	Init();
}

void Frighten::Update(const float& dt)
{
	float stateTime = stateClock.getElapsedTime().asSeconds();

	if (glob_powerOn) {

		ghost->turnAround();
		stateClock.restart().asSeconds();
	}

	if (stateTime > glob_frightenModeTimer) {
		Exit(previousState);
		return;
	}
	if (ghost->turningPointReached()) {
	
		ghost->chooseRandomDirection();
	
	}
	Animate(stateTime, dt);
	ghost->moveOn(dt);
}

void Frighten::Animate(const float &stateTime,const float &dt)
{
	if (stateTime < 5) {
		ghost->animation.Update(4, dt, ghost->ANIMATIONSWITCHTIME);
	}
	else {
		ghost->animation.UpdateCustomOfColumns(5,4, dt, 0.25f); //This row of the texture consists of 4 columns to easily update the animation.
	}

}

void Frighten::Init()
{
	ghost->isFrightened = true;
	ghost->limitspeed = true;
	//Flip direction if can
	ghost->turnAround();
	ghost->currentState = eFrighten;
	
}

void Frighten::Exit(const ghostState& state)
{
	ghost->limitspeed = false;
	ghost->isFrightened = false;

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