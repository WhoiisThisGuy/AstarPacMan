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
	unsigned short int animationCounter;//How many times will the white ghost texture flash before the state expires.
	static unsigned short int eatenNum; //number of eaten ghost to know which score texture is next
private:
	void Animate(const float &stateTime,const float &dt);
	void Init() override;
	void Exit(const ghostState&) override; //Clean up
	

};

