#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <sstream>
#include "Map.h"
#include "Pacman.h"

#define PacmanMovementSpeed 200.0f
#define Videomode 1600.0f, 1000.0f

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
	//A fõhõs

	Map map;
	//pálya
};
