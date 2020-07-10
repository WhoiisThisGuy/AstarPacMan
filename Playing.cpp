#include "Playing.h"
#include "Menu.h"

#include <iostream>

Playing::Playing() {

	if (!backgroundTexture.loadFromFile("Textures/background.png"))
		std::cout << "could not load background file";
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0.0f, 4*24); //4*24 is the extra 4 row
	paused = false;
}

void Playing::Updatedt()
{

	dt = deltaClock.restart().asSeconds();

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

	Updatedt();
	
	if (pacman.Update(dt)) { //if returns true = gameover, else go on
		Game_Over = false;
		return new Menu();
	} 

	map.Update();

	blinky.Update(dt);
	inky.Update(dt);
	pinky.Update(dt);
	clyde.Update(dt);

	if (glob_powerOn)
		glob_powerOn = false;

	Render(window);

	return NULL;
}