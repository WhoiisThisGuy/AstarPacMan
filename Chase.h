#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Chase :
	public ActorState
{

public:
	Chase(Ghost*);

	~Chase() {};
	void Update() override; //Update
	void Init() override;
private:
	Ghost* ghost;


private:
	
	void Exit() override; //Clean up
};

