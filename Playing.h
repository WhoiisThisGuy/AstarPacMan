#pragma once
#include "GameState.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Pacman.h"

class Playing : public GameState
{

public:
	Playing();
	GameState* Update(RenderWindow&);
	void Render(RenderWindow& window);
	
public:
	Clock deltaClock;
	//Game futáshoz
	Sprite backgroundSprite;

	Event event;
	Texture backgroundTexture; //This is for the Game class.

	Map map;
	//pálya

	Pacman pacman;
	//The hero

	Blinky blinky;
	Pinky pinky;
	Inky inky;
	Clyde clyde;
	//Chasers
private:
	void Updatedt();
private:
	float dt;
	bool paused;
};

