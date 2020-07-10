#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

class GameState
{
public:
	GameState() {};
	virtual GameState* Update(RenderWindow&) = 0;

};

