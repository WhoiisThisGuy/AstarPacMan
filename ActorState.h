#pragma once
#include <math.h>
#include "SFML/Graphics.hpp"
#include <iostream>
#include "LevelVariables.h"
#include "Ghost.h"

using namespace sf;

#ifndef H_ACTSTATE
#define H_ACTSTATE

enum ghostState {eGhostHouse,eScatter,eChase,eFrighten,eGameOver,eEaten,eTunneling}; //e-enum

class ActorState
{
public:
	ActorState() { stateClock.restart().asSeconds(); }
	virtual ~ActorState() { std::cout << "ActorState destructed" << std::endl; }
	virtual void Update(const float& dt) = 0; //Update
	
protected:
	
	Clock stateClock;
	uint16_t STATENUMBER; //how many times the ghost had been in this state
private:
	virtual void Init() = 0;
	virtual void Exit(const ghostState&) = 0; //Set up next to next state
};

#endif

