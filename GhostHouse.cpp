#include "GhostHouse.h"
#include "Scatter.h"
#include "Frighten.h"

GhostHouse::GhostHouse(Ghost* p_ghost)
{
	
	ghost = p_ghost;
	Init();
}


/* This is a really wierd solution to come out from ghost house. */

void GhostHouse::Update(const float &dt)
{
	
	if (Game_Over) { // && stateTime > 2
		Exit(eGameOver);
		return;
	}

	float stateTime = stateClock.getElapsedTime().asSeconds();



	Animate(stateTime, dt);

	if (ghost->firstcomeout) {
		if (stateTime > ghost->activateTimer && ghost->moveToFourteenDotThirtyFive()) {
			ghost->firstcomeout = false;
		}
		else {
			ghost->moveUpAndDown();
		}
		
	}
	else if (!ghost->isActive()) {	
		ghost->comeOutFromHouse();
	}
	else {
		Exit();
		return;
	}
	ghost->moveOn(dt);
}

void GhostHouse::Init()
{
	ghost->currentState = eGhostHouse;
	stateClock.restart().asSeconds();
	ghost->limitspeed = true;

}

void GhostHouse::Exit(const ghostState& state){

	ghost->limitspeed = false;
	ghost->calculateNewDirection();
	ghost->setState(new Scatter(ghost));
}

void GhostHouse::Animate(const float& stateTime, const float& dt)
{
	if (ghost->isFrightened) {
		if (stateTime < 5) {
			ghost->animation.Update(4, dt, ghost->ANIMATIONSWITCHTIME);
		}
		else {
			ghost->animation.UpdateCustomOfColumns(5, 4, dt, 0.25f); //This row of the texture consists of 4 columns to easily update the animation.
		}
	}
	else
		ghost->animation.Update(ghost->rowToSetForAnimation(), dt, ghost->ANIMATIONSWITCHTIME);

}