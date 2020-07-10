#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Eaten :
	public ActorState
{

public:
	Eaten(Ghost* ghostToHandle, ghostState& prevState);
	virtual void Update(const float& dt);
private:
	Ghost* ghost;
	ghostState previousState;
private:
	void Init();
	void Exit(const ghostState&); //Clean up

};

