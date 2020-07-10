#include "Scatter.h"
#include "Chase.h"
#include "Frighten.h"
#include "GhostGameOver.h"

Scatter::Scatter(Ghost* ghostToHandle) {
	
	ghost = ghostToHandle;	
	
	Init();
}

void Scatter::Update(const float &dt)
{
	
	if (Game_Over) {
		Exit(eGameOver);
		return;
	}

	float stateTime = stateClock.getElapsedTime().asSeconds();

	ghost->animation.Update(ghost->rowToSetForAnimation(), dt, ghost->ANIMATIONSWITCHTIME);


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

	if (stateTime > 8) {
		Exit();
		return;
	}
	if(ghost->turningPointReached()){
		ghost->calculateNewDirection();
	}
	ghost->moveOn(dt);
}

void Scatter::Init()
{
	stateClock.restart().asSeconds();
	ghost->currentState = eScatter;
	ghost->setScatterTargetNode();
	//ghost->calculateNewDirection();
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

	}
	
	//******************************
	//Dont use ghost from this point cause of deletion
}

