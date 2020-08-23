#include "Playing.h"
#include "Menu.h"

#include <iostream>

Playing::Playing() {

	LEVELNUMBER = 0;

	if (!backgroundTexture.loadFromFile("Textures/background2.png"))
		std::cout << "could not load background file";
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0.0f, 4*24); //4*24 is the extra 4 row
	
	pacmanTexture.loadFromFile(PACMANTEXTUREPATH);
	paused = false;
	fToUpdate = &Playing::UpdateGameStart;

	readyText.setFillColor(Color::Yellow);
	readyText.setFont(font);
	readyText.setCharacterSize(37);
	readyText.setPosition(11*CELLSIZE,21*CELLSIZE);
	readyText.setString("READY!");

	returnState = NULL;


	blinky.SetStartParams();
	inky.SetStartParams();
	pinky.SetStartParams();
	clyde.SetStartParams();

	//map.GhostHousePriority.push(pinky.GetGhostPriorityNumber());
	//map.GhostHousePriority.push(inky.GetGhostPriorityNumber());
	//map.GhostHousePriority.push(clyde.GetGhostPriorityNumber());
	
}

Playing::~Playing()
{
	cout << "Playing destructed" << endl;
}

void Playing::Updatedt()
{
	dt = deltaClock.restart().asSeconds();
	//gameclock.restart().asSeconds()
}

void Playing::UpdateGameWinAnimation(const float& dt)
{

	backgroundSprite.setTextureRect(backgroundAnimation[whiteorblue]);
	whiteorblue = !whiteorblue;
	StartGameWinAnimationAfter = 0;
	
}

void Playing::GhostsVisible(bool b)
{
	blinky.visible = b;
	inky.visible = b;
	pinky.visible = b;
	clyde.visible = b;
}

void Playing::UpdateGamePlay()
{
	if (paused) {
		pauseTimePassed += dt; //counting time to get back from paused mode.
		if (pauseTimePassed > Map::pauseTime) { //if pause time is finished check if I need to set up game win or game over mode
			paused = false;
			Map::pauseTime = 0;
			pauseTimePassed = 0;
			if (Game_Over) {
				pacman.InitDeathAnimation();
				GhostsVisible(false);
				fToUpdate = &Playing::UpdateGameOver;//func to update change here
				returnState = NULL;
				return;
			}
			else if (Game_Win) {
				
				GhostsVisible(false);
				fToUpdate = &Playing::UpdateGameWin;//func to update change here
				//text.setString("READY!");
				returnState = NULL;
				return;
			}
		}
	}

	map.Update();

	pacman.Update(dt);

	blinky.Update(dt);
	inky.Update(dt);
	pinky.Update(dt);
	clyde.Update(dt);

	if (glob_powerOn) /* Once all the ghosts are updated to change into frighten state -> turn off the power on mode. */
		glob_powerOn = false;

	returnState = NULL;
	return;
}

void Playing::UpdateGameWin()
{

	TimePassedFromWinAnimationStart += dt;

	if (TimePassedFromWinAnimationStart < FinishWinAnimationAfter) {
		UpdateGameWinAnimation();
	}
	else {
		
		TimePassedFromWinAnimationStart = 0;
		backgroundSprite.setTextureRect(backgroundAnimation[0]);

		GhostsVisible(true);

		readyText.setString("Ready!");

		map.TurnOnPellets();
		//reload pellets

		if(LEVELNUMBER<20)
			++LEVELNUMBER;
		//update level variable
		
		blinky.SetStartParams();
		inky.SetStartParams();
		pinky.SetStartParams();
		clyde.SetStartParams();
		pacman.SetStartState();

		fToUpdate = &Playing::UpdateGameStart;
		return;
	}
	
	returnState = NULL;
}

void Playing::UpdateGameWinAnimation()
{
	TimePassedWinAnimation += dt;

	if (TimePassedWinAnimation > SwitchWinAnimationAfter) {
		backgroundSprite.setTextureRect(backgroundAnimation[whiteorblue]);
		whiteorblue = !whiteorblue;
		StartGameWinAnimationAfter = 0;
		TimePassedWinAnimation = 0;
	}
}

void Playing::UpdateGameOver()
{

	if (pacman.UpdateDeathAnimation(dt)) {
		
		pacman.DecreaseHealth();
		if (pacman.GetHealthValue() <= 0) { //Game over go back to main menu
			returnState = new Menu();
			return;
		}
		else { //Restart the level
			pacman.SetStartState();
			blinky.SetStartParams();
			inky.SetStartParams();
			pinky.SetStartParams();
			clyde.SetStartParams();
			readyText.setString("Ready!");
			GhostsVisible(true);
			fToUpdate = &Playing::UpdateGameStart;
			map.ClearGhostHousePriorityQueue();
			return;
		}
	}

	returnState = NULL;
}

void Playing::UpdateGameStart()
{

	TimePassedFromWinAnimationStart += dt;
	SpecialCounter = false;
	if (TimePassedFromWinAnimationStart > 3) {
		
		TimePassedFromWinAnimationStart = 0;
		GhostsVisible(true);
		/* Reset all level variable here. */
		Game_Win = false;
		Game_Over = false;
		elroy1 = false;
		elroy2 = true;

		pacman.SetStartState();//setBack Start positions
		blinky.SetStartState();
		inky.SetStartState();
		pinky.SetStartState();
		clyde.SetStartState();
		map.GhostHousePriority.push(inky.GetGhostPriorityNumber());
		map.GhostHousePriority.push(clyde.GetGhostPriorityNumber());
		fToUpdate = &Playing::UpdateGamePlay;
		readyText.setString("");
		return;
	}

	returnState = NULL;
}

void Playing::Render(RenderWindow& window) {

	window.clear();
	
	window.draw(backgroundSprite);
	map.Draw(window);
	blinky.Draw(window);
	inky.Draw(window);
	pacman.Draw(window);
	pinky.Draw(window);
	clyde.Draw(window);
	if(readyText.getString() != "")
		window.draw(readyText);

	window.display();
}

GameState* Playing::Update(RenderWindow& window)
{
	
	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			//window.close();
			return new Menu();
		}
		if (event.type == sf::Event::Closed) {
			window.close();
			return NULL;
		}
	}
	Updatedt();
	(this->*fToUpdate)();

	Render(window);

	return returnState;
}