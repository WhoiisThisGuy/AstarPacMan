#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Frighten :
	public ActorState
{

public:
	Frighten(Ghost*, ghostState);
	~Frighten() {};
	void Update(const float &dt) override; //Update
private:
	Ghost* ghost;
	ghostState previousState;
private:
	void Animate(const float &stateTime,const float &dt);
	void Init() override;
	void Exit(const ghostState&) override; //Clean up

};

