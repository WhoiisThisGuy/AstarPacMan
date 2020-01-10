#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <sstream>
#include "Pacman.h"
#include "Map.h"

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
	//Game fut�shoz

	sf::Texture PacmanTexture;
	Pacman* pacman;
	//A f�h�s

	Map map;
	//p�lya
};
