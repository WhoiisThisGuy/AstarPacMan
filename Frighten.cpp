#include "Frighten.h"
#include "Scatter.h"
#include "Chase.h"
#include "Eaten.h"
#include "Tunneling.h"
#include "GhostGameOver.h"

unsigned short int Frighten::eatenNum = 0;

Frighten::Frighten(Ghost* ghostToHandle, ghostState prevState) {
	
	ghost = ghostToHandle;
	previousState = prevState;
	//std::cout << "SCATTER\n";
	ghost->isFrightened = true;
	ghost->currentState = eFrighten;
	Init();
}

void Frighten::Update(const float& dt)
{
	float stateTime = stateClock.getElapsedTime().asSeconds();

	if (paused)
		return;

	if (Game_Over || Game_Win) {
		Exit(eGameOver);
		return;
	}

	//if eaten exit here
	if (ghost->collideWithPacman()) {
		paused = true;
		ghost->animation.setScoreImage(eatenNum);
		ghost->UpdateTexture();

		++eatenNum;
		if (eatenNum > 3)
			eatenNum = 0;
		Exit(eEaten);
		return;
	}

	if (animationCounter > 4) {
		Exit(previousState);
		return;
	}
	if (ghost->turningPointReached() || ghost->tunnelPointReached()) {
		if (ghost->inTunnel) {
			Exit(eTunneling);
			return;
		} 
	
		ghost->chooseRandomDirection();
	
	}

	Animate(stateTime, dt);
	ghost->UpdateTexture();
	if (glob_powerOn) {

		Init();
	}

	ghost->moveOn(dt);
}

void Frighten::Animate(const float &stateTime,const float &dt)
{
	if (stateTime > 4) { 
		ghost->animation.lastImage = ghost->animation.firstImage + 3;
		ghost->ANIMATIONSWITCHTIME = 0.08;
		ghost->animation.UpdateFrightenAnimation(dt, ghost->ANIMATIONSWITCHTIME,animationCounter);
	}
	else {
		ghost->animation.Update(dt, ghost->ANIMATIONSWITCHTIME);
	}
	
}

void Frighten::Init()
{
	ghost->speed = levelValues[LEVELNUMBER][12];
	ghost->turnAround();
	animationCounter = 0;
	stateClock.restart().asSeconds();
	//Flip direction if can
	ghost->animation.imageToSet.y = 0;
	ghost->animation.firstImage = 8;
	ghost->animation.imageToSet.x = ghost->animation.firstImage;
	ghost->animation.lastImage = ghost->animation.firstImage + 1;
	
}

void Frighten::Exit(const ghostState& state)
{
	ghost->isFrightened = false;

	ghost->ANIMATIONSWITCHTIME = 0.25;

	switch (state) {

		case eChase:
			ghost->turnAround();
			ghost->setState(new Chase(ghost));
			if(eatenNum > 0)
				eatenNum = 0;
			break;
		case eScatter:
			ghost->turnAround();
			ghost->setState(new Scatter(ghost));
			if (eatenNum > 0)
				eatenNum = 0;
			break;
		case eFrighten:
			ghost->turnAround();
			ghost->setState(new Frighten(ghost, state));
			break;
		case eEaten:
			ghost->setState(new Eaten(ghost, state, eatenNum));
			break;
		case eTunneling:
			ghost->setState(new Tunneling(ghost));
			break;
		case eGameOver:
			ghost->setState(new GhostGameOver(ghost));
			break;
	}
	
}