#include "GhostGameOver.h"

GhostGameOver::GhostGameOver(Ghost* ghostToHandle)
{
	ghost = ghostToHandle;
	
}

void GhostGameOver::Update(const float& dt)
{
	if (stateClock.getElapsedTime().asSeconds() > 2) {
		ghost->visible = false;
	}

	ghost->animation.Update(ghost->rowToSetForAnimation(), dt, ghost->ANIMATIONSWITCHTIME);
	
}

void GhostGameOver::Init()
{
	stateClock.restart().asSeconds();
}

void GhostGameOver::Exit(const ghostState& state)
{
}
