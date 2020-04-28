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

private:
	Ghost* ghost;
	
private:
	void Init() override;
	
	void Exit() override; //Clean up
};

