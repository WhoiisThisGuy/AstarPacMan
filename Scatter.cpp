#include "Scatter.h"
#include "Chase.h"

Scatter::Scatter(Ghost* ghostToHandle) {
	ghost = ghostToHandle;	
	//std::cout << "SCATTER\n";
	Init();
}

void Scatter::Update()
{

	if (ghost->nextNodeReached()) { //Check for next node.
		//if()
		if (stateClock.getElapsedTime().asSeconds() > 7) {
			Exit();
			return;
		}
		ghost->calculateNewNextNode(); //Get new next node.
		ghost->setDirection();
	}
}

void Scatter::Init()
{
	stateClock.restart().asSeconds();
	//Flip direction if can
	ghost->turnAround();
	ghost->setScatterTargetNode();
	ghost->calculateNewNextNode();
	ghost->setDirection();
}

void Scatter::Exit()
{

	ghost->setState(new Chase(ghost));

}
