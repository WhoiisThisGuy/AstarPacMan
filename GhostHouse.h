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


private:
	void Animate(const float& stateTime,const float& dt);
	void Init() override;
	void Exit(const ghostState& state = eScatter) override; //Clean up

};

