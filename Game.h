#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <sstream>
#include <memory.h>
#include "Blinky.h"
#include "Pacman.h"
#include "Map.h"

#define VIDEOMODE 1600.0f, 1000.0f

class Game {

public:

	Game();
	~Game();
	void run();
	void Update();
	void UpdateDt();
	void UpdateSfmlEvents();
	void Render();

private:

	sf::Text PacManPosText;
	
	sf::Font font;
	//Info kiiras pacman poziciojarol

	float dt;
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock deltaClock;
	//Game futáshoz

	sf::Texture PacmanTexture;
	Pacman* pacman;
	//The hero
	
	sf::Texture BlinkyTexture;
	Blinky* blinky;
	//Chasers

	Map map;
	//pálya
};
