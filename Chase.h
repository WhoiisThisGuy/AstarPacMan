#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Chase :
	public ActorState
{

public:
	Chase(Ghost*);
	~Chase() {};
	void Update(const float &) override; //Update
	
private:
	Ghost* ghost;
private:
	void Init() override;
	void Exit(const ghostState& state = eScatter) override; //Clean up
};

