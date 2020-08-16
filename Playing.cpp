#include "Playing.h"
#include "Menu.h"

#include <iostream>

Playing::Playing() {

	if (!backgroundTexture.loadFromFile("Textures/background2.png"))
		std::cout << "could not load background file";
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0.0f, 4*24); //4*24 is the extra 4 row
	
	pacmanTexture.loadFromFile(PACMANTEXTUREPATH);
	paused = false;
	
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

void Playing::Render(RenderWindow& window) {

	window.clear();
	
	window.draw(backgroundSprite);
	map.Draw(window);
	blinky.Draw(window);
	inky.Draw(window);
	pacman.Draw(window);
	pinky.Draw(window);
	clyde.Draw(window);


	window.display();
}

GameState* Playing::Update(RenderWindow& window)
{


	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			return NULL;
		}
		if (event.type == sf::Event::Closed) {
			window.close();
			return NULL;
		}
	}
	if (paused) { //When a ghost is eaten
		if (deltaClock.getElapsedTime().asSeconds() > 1) {
			paused = false;
			Updatedt();
		}

		return NULL;
	}


	Updatedt();



	map.Update();

	if (Game_Win) {
		time_passed += dt;
		if (time_passed > 0.55) {
			backgroundSprite.setTextureRect(backgroundAnimation[whiteorblue]);
			whiteorblue = !whiteorblue;
			time_passed = 0;
		}
		Render(window);
		return NULL;
	}

	if (pacman.Update(dt,window)) { //if returns true = gameover, else go on
		Game_Over = false;
		return new Menu();
	} 



	blinky.Update(dt);
	inky.Update(dt);
	pinky.Update(dt);
	clyde.Update(dt);
	


	if (glob_powerOn) /* Once all the ghosts are updated to change into frighten state -> turn off the power on mode. */
		glob_powerOn = false;



	Render(window);

	return NULL;
}