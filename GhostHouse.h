#pragma once
#include "ActorState.h"
#include "Ghost.h"
class GhostHouse :
	public ActorState
{

public:
	GhostHouse(Ghost*);

	~GhostHouse() {};
	void Update() override; //Update
	
private:
	Ghost* ghost;


private:
	void Init() override;
	void Exit() override; //Clean up

};

