#include "Scatter.h"
#include "Chase.h"
#include "Frighten.h"
#include "GhostGameOver.h"
#include "Tunneling.h"

Scatter::Scatter(Ghost* ghostToHandle) {
	
	ghost = ghostToHandle;	
	
	Init();
}

void Scatter::Update(const float &dt)
{
	if (paused)
		return;

	if (Game_Over) {
		Exit(eGameOver);
		return;
	}

	float stateTime = stateClock.getElapsedTime().asSeconds();

	ghost->animation.Update(dt, ghost->ANIMATIONSWITCHTIME);
	ghost->UpdateTexture();

	/*Collision check*/
	if (!Game_Over && ghost->collideWithPacman())
	{
		Game_Over = true;

		Exit(eGameOver);
		return;
	}

	if (glob_powerOn && !ghost->isFrightened) {

		Exit(eFrighten);
		return;
	}

	if (stateTime > scatterTimings[STATENUMBER][LEVELNUMBER]) { //
		Exit();
		return;
	}

	if(ghost->turningPointReached() || ghost->tunnelPointReached()){

		if (ghost->inTunnel) {
			Exit(eTunneling);
			return;
		}

		ghost->calculateNewDirection();
		ghost->animation.firstImage = ghost->getDirectionForAnimation();
		ghost->animation.imageToSet.x = ghost->animation.firstImage;
		ghost->animation.lastImage = ghost->animation.firstImage + 1;
	}

	ghost->moveOn(dt);
}

void Scatter::Init()
{
	ghost->currentState = eScatter;
	++STATENUMBER;

	ghost->speed = elroy1 ? levelValues[LEVELNUMBER][6] : elroy2 ? levelValues[LEVELNUMBER][8] : levelValues[LEVELNUMBER][3];

	stateClock.restart().asSeconds();
	ghost->animation.selectBox = { 16,16 }; //default 16x16 for ghosts
	ghost->animation.uvRect.width = 14;
	ghost->animation.uvRect.height = 14;
	
	ghost->setScatterTargetNode();
	ghost->animation.firstImage = ghost->getDirectionForAnimation();
	ghost->animation.imageToSet.x = ghost->animation.firstImage;
	ghost->animation.imageToSet.y = ghost->rowForAnimation;
	ghost->animation.lastImage = ghost->animation.firstImage+1;

}

void Scatter::Exit(const ghostState& state)
{
	switch (state) {

	case eChase:
		ghost->turnAround();
		ghost->setState(new Chase(ghost));
		break;
	case eFrighten:
		ghost->turnAround();
		ghost->setState(new Frighten(ghost, ghost->currentState));
		break;
	case eGameOver:
		ghost->setState(new GhostGameOver(ghost));
		break;
	case eTunneling:
		ghost->setState(new Tunneling(ghost));
		break;
	}
	
	//******************************
	//Dont use ghost from this point cause of deletion
}

