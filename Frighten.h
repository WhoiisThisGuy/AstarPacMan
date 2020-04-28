#pragma once
#include "ActorState.h"
#include "Ghost.h"

class Frighten :
	public ActorState
{

public:
	Frighten(Ghost*);
	~Frighten() {};
	void Update() override; //Update
	
private:
	Ghost* ghost;

private:
	void Init() override;
	void Exit() override; //Clean up

};

