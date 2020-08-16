#pragma once
#include "LevelVariables.h"
#include <iostream>

using namespace sf;


class GameState
{
public:
	GameState() { font.loadFromFile("Joystix.TTF"); }
	virtual ~GameState() { std::cout << "GameState destructed" << std::endl; }
	virtual GameState* Update(RenderWindow&) = 0;

};

