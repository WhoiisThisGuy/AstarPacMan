#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Eaten :
	public ActorState
{

public:
	Eaten(Ghost* ghostToHandle,const ghostState& prevState, const unsigned short int&);
	virtual void Update(const float& dt);
private:
	Ghost* ghost;
	ghostState previousState;
private:
	void Init();
	void Exit(const ghostState&); //Clean up

};

