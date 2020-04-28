#pragma once
#include <math.h>
#include "SFML/Graphics.hpp"
#include <iostream>


using namespace sf;

#ifndef H_ACTSTATE
#define H_ACTSTATE
class ActorState
{
public:
	ActorState() { stateClock.restart().asSeconds(); }
	virtual ~ActorState() {};
	virtual void Update() = 0; //Update
protected:
	Clock stateClock;
private:
	virtual void Init() = 0;
	virtual void Exit() = 0; //Clean up
};

#endif

