#include "Chase.h"
#include "Scatter.h"


Chase::Chase(Ghost * pghost) {
	ghost = pghost;
	//std::cout << "CHASE\n";
	Init();
}

void Chase::Update()
{

	if (ghost->nextNodeReached()) { //Check for next node.
		if (stateClock.getElapsedTime().asSeconds() > 13) {
			Exit();
			return;
		}
		ghost->setChaseTargetNode();
		ghost->calculateNewNextNode(); //Get new next node.
		ghost->setDirection();
	}

}

void Chase::Init()
{
	stateClock.restart().asSeconds();
	//Flip direction
	ghost->turnAround();
	ghost->setChaseTargetNode();
	ghost->calculateNewNextNode();
	ghost->setDirection();

}

void Chase::Exit()
{
	ghost->setState(new Scatter(ghost));
}
