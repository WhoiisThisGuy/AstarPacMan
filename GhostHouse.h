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
	void Init() override;
private:
	Ghost* ghost;


private:

	void Exit() override; //Clean up

};

