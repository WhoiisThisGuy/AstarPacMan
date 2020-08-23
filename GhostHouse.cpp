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

	if (Game_Over || Game_Win) {
		Exit(eGameOver);
		return;
	}

	if (paused)
		return;


	if (!ghost->ActivateGhost && (!Map::GhostHousePriority.empty() && ghost->GetGhostPriorityNumber() == Map::GhostHousePriority.top())) { //am I topPriority
		
		if (!DotCounterActive) {
			Map::DotCounterForGhosts = &DotCounter; //Turn on counting dots in map
			DotCounterActive = true;
		}
		if (DotCounter >= 5)
			cout<<"okgeci"<<endl;
		if (DotCounter >= ghost->GetActivationDotLimit() || Map::ClockSinceLastDotEaten.getElapsedTime().asSeconds() >= (LEVELNUMBER >= 5 ? 3 : 4)) {//

			ghost->ActivateGhost = true;
			Map::GhostHousePriority.pop();
		}
	}

	if (ghost->ActivateGhost) {
		if (ghost->moveToFourteenDotThirtyFive()) {
			if (ghost->comeOutFromHouse()) {
				Exit(eScatter);
				return;
			}
		}
				
	}
	else {
		ghost->moveUpAndDown();

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
	ghost->currentState = eGhostHouse;
	


	DotCounterActive = false;
	DotCounter = 0;

	
	ghost->speed = levelValues[LEVELNUMBER][5];
	ghost->setDirection(ghost->startDirection);
	ghost->firstcomeout = true;
	ghost->active = false;
	
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
	ghost->active = true;
	ghost->calculateNewDirection();
	//Map::DotCounterForGhosts = NULL; //Turn off counting in map
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