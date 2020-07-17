#include "Tunneling.h"
#include "Chase.h"
#include "GhostGameOver.h"


Tunneling::Tunneling(Ghost* ghostToHandle) {

	ghost = ghostToHandle;
	ghost->limitspeed = true;
	ghost->currentState = eFrighten;
	Init();
}

void Tunneling::Update(const float& dt)
{

	float stateTime = stateClock.getElapsedTime().asSeconds();

	if (paused)
		return;
	if (Game_Over) {
		Exit(eGameOver);
		return;
	}
	//if eaten exit here
	if (ghost->collideWithPacman()) {
		Game_Over = true;
		Exit(eGameOver);
		return;
	}
	
	ghost->animation.Update(dt, ghost->ANIMATIONSWITCHTIME);
	ghost->UpdateTexture();
	(this->*fToUpdate)(dt);
	return; //Return immediatley
}

void Tunneling::TunnelingIn(const float& dt)
{
	if (ghost->tunnelTeleport()) {
		fToUpdate = &Tunneling::TunnelingOut;	
	}
	ghost->moveOn(dt);
}

void Tunneling::TunnelingOut(const float& dt)
{
	if (ghost->turningPointReached())
	{
		ghost->inTunnel = false;
		Exit(eChase);
		return;
	}
	ghost->moveOn(dt);
}

void Tunneling::Init()
{

	fToUpdate = &Tunneling::TunnelingIn;
	
	stateClock.restart().asSeconds();
	ghost->speed = 120;
	ghost->currentState = eTunneling;
	ghost->animation.firstImage = ghost->getDirectionForAnimation();
	ghost->animation.imageToSet.x = ghost->animation.firstImage;
	ghost->animation.imageToSet.y = ghost->rowForAnimation;
	ghost->animation.lastImage = 2;
}


void Tunneling::Exit(const ghostState& state)
{

	switch (state) {
	case eChase:

		ghost->setState(new Chase(ghost));
		break;
	case eGameOver:
		ghost->setState(new GhostGameOver(ghost));
		break;
	}
}