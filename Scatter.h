#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Scatter :
	public ActorState
{

public:
	Scatter(Ghost*);
	~Scatter() {};
	void Update() override; //Update
	void Init() override;
private:
	Ghost* ghost;
	
private:

	
	void Exit() override; //Clean up
};

