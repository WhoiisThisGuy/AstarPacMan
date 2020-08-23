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
	void UpdateGameWinAnimation(const float& );

	void GhostsVisible(bool);

	void(Playing::* fToUpdate)();
	void UpdateGamePlay();
	void UpdateGameWin();
	void UpdateGameWinAnimation();
	void UpdateGameOver();
	void UpdateGameStart();

private:
	Text readyText;
	

	//pausing game
	float pauseTimePassed = 0;

	//win animation
	unsigned short int StartGameWinAnimationAfter = 2;
	float TimePassedWinAnimation = 0;
	const float SwitchWinAnimationAfter = 0.3f;
	const float FinishWinAnimationAfter = 3;
	float TimePassedFromWinAnimationStart;
	bool whiteorblue = false; //blue or white for the animation
	IntRect backgroundAnimation[2] = {IntRect(0,0,672,744),IntRect(694,0,672,744)};


	//deltatime
	float dt;
	/* Textures */
	Texture ghostsTexture;
	Texture pacmanTexture;

	//Return this to game object, every Update function will set it in properly.
	GameState* returnState;
};

