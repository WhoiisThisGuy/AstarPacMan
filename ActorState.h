#pragma once
#include <math.h>
#include "SFML/Graphics.hpp"
#include <iostream>


using namespace sf;

#ifndef H_ACTSTATE
#define H_ACTSTATE

enum ghostState {eGhostHouse,eScatter,eChase,eFrighten,eGameOver,eEaten}; //e-enum

class ActorState
{
public:
	ActorState() { stateClock.restart().asSeconds(); }
	virtual ~ActorState() {};
	virtual void Update(const float& dt) = 0; //Update
	ghostState getcurrentState() { return currentState; };
protected:
	
	Clock stateClock;
	
private:
	virtual void Init() = 0;
	virtual void Exit(const ghostState&) = 0; //Clean up
};

#endif

