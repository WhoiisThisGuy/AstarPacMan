#include "Chase.h"
#include "Scatter.h"
#include "Frighten.h"
#include "GhostGameOver.h"


Chase::Chase(Ghost * pghost) {
	
	ghost = pghost;
	//std::cout << "CHASE\n";
	Init();
}

void Chase::Update(const float& dt)
{
	if (Game_Over) {
		Exit(eGameOver);
		return;
	}

	float stateTime = stateClock.getElapsedTime().asSeconds();

	if (!Game_Over && ghost->collideWithPacman())
	{
		Game_Over = true;
		Exit(eGameOver);
		return;
	}



	ghost->animation.Update(ghost->rowToSetForAnimation(), dt, ghost->ANIMATIONSWITCHTIME);
	if (glob_powerOn && !ghost->isFrightened) {
	
		Exit(eFrighten);
		return;
	}



	if (stateTime > 13) {
		Exit();
		return;
	}
	
	if (ghost->turningPointReached()) {
		ghost->setChaseTargetNode();
		ghost->calculateNewDirection();
	}
	ghost->moveOn(dt);
}

void Chase::Init()
{
	stateClock.restart().asSeconds();
	//Flip direction
	//ghost->calculateNewDirection();
	ghost->currentState = eChase;
}

void Chase::Exit(const ghostState& state)
{
	ghost->turnAround();

	switch (state) {
	case eScatter:
		ghost->setState(new Scatter(ghost));
		break;
	case eFrighten:
		ghost->turnAround();
		ghost->setState(new Frighten(ghost, ghost->currentState));
		break;
	case eGameOver:
		ghost->setState(new GhostGameOver(ghost));
		break;
	}
}