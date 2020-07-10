#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Scatter :
	public ActorState
{

public:
	Scatter(Ghost*);
	~Scatter() {};
	void Update(const float &dt) override; //Update
private:
	Ghost* ghost;
	
private:
	void Init() override;
	
	void Exit(const ghostState& state = eChase) override; //Clean up
};

