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
	~Playing();
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
	Text readyText;

	float time_passed = 0;
	float startWinAnimationAfter = 1.0f;
	bool whiteorblue = false; //blue or white for the animation
	IntRect backgroundAnimation[2] = {IntRect(0,0,672,744),IntRect(694,0,672,744)};
	float dt;
	/* Textures */
	Texture ghostsTexture;
	Texture pacmanTexture;
};

