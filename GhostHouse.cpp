#include "GhostHouse.h"
#include "Scatter.h"


GhostHouse::GhostHouse(Ghost* p_ghost)
{
	ghost = p_ghost;
}

void GhostHouse::Update()
{

	if (ghost->firstcomeout) {
		if (stateClock.getElapsedTime().asSeconds() > ghost->activateTimer) {
			if (ghost->moveToFourteenDotThirtyFive()) {
				ghost->firstcomeout = false;
			}
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
	}
	
}

void GhostHouse::Init()
{

	stateClock.restart().asSeconds();
	ghost->limitspeed = true;

}

void GhostHouse::Exit()
{

	ghost->limitspeed = false;
	ghost->setState(new Scatter(ghost));
}
