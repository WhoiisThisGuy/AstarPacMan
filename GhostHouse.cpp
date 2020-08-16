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
	if (paused)
		return;

	if (Game_Over || Game_Win) { // && stateTime > 2
		Exit(eGameOver);
		return;
	}

	float stateTime = stateClock.getElapsedTime().asSeconds();
	
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
	ghost->animation.firstImage = ghost->getDirectionForAnimation();
	ghost->animation.imageToSet.x = ghost->animation.firstImage;
	ghost->animation.lastImage = ghost->animation.firstImage + 1;
	ghost->animation.Update(dt, ghost->ANIMATIONSWITCHTIME);
	ghost->UpdateTexture();
	ghost->moveOn(dt);
}

void GhostHouse::Init()
{
	
	ghost->speed = levelValues[LEVELNUMBER][5];
	ghost->setDirection(ghost->startDirection);
	ghost->firstcomeout = true;
	ghost->active = false;
	ghost->currentState = eGhostHouse;
	stateClock.restart().asSeconds();

	ghost->animation.selectBox = { 16,16 }; //default 16x16 for ghosts
	ghost->animation.uvRect.width = 14;
	ghost->animation.uvRect.height = 14;

	ghost->animation.firstImage = ghost->getDirectionForAnimation();
	ghost->animation.imageToSet.x = ghost->animation.firstImage;
	ghost->animation.imageToSet.y = ghost->rowForAnimation;
	ghost->animation.lastImage = ghost->animation.firstImage + 1;

}

void GhostHouse::Exit(const ghostState& state){

	ghost->calculateNewDirection();
	ghost->setState(new Scatter(ghost));
}

//void GhostHouse::Animate(const float& stateTime, const float& dt)
//{
//	if (ghost->isFrightened) {
//		if (stateTime < 5) {
//			ghost->animation.Update(4, dt, ghost->ANIMATIONSWITCHTIME);
//		}
//		else {
//			ghost->animation.UpdateCustomOfColumns(5, 4, dt, 0.25f); //This row of the texture consists of 4 columns to easily update the animation.
//		}
//	}
//	else
//		ghost->animation.Update(ghost->rowToSetForAnimation(), dt, ghost->ANIMATIONSWITCHTIME);
//
//}