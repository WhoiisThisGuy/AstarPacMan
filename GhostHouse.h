#pragma once
#include "ActorState.h"
#include "Ghost.h"
class GhostHouse :
	public ActorState
{

public:
	GhostHouse(Ghost*);

	~GhostHouse() {};
	void Update(const float& dt) override; //Update
private:
	Ghost* ghost;
	unsigned short int DotCounter;
	bool DotCounterActive;
private:
	void Init() override;
	void Exit(const ghostState& state = eScatter) override; //Clean up

};

