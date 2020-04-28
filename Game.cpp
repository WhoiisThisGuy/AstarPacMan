﻿#include "Game.h"
#include "LoadFile.h"
#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>
#include <memory>

using std::cout;

Game::Game()
	: window(sf::VideoMode(680,900), "PacmanAstar", sf::Style::Close | sf::Style::Titlebar ),
	dt(0.0)
{	
	window.setPosition(Vector2i(0,0));
	if (!loadFiles())
		cout << "Failed to load a file.";
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0.0f,MAPOFFSET);


	//font.loadFromFile("consola.ttf");
	window.setFramerateLimit(60);
	//pacManTempCoordsOnLevel = pacman.getTempCoordsOnLevel();
}

Game::~Game() {
	
}

void Game::run()
{

	while (window.isOpen())
	{
		Update();
		Render();
	}

}

void Game::UpdateDt()
{
	dt = deltaClock.restart().asSeconds();

}

void Game::Update()
{
	UpdateDt();
	UpdateSfmlEvents();
	
	pacman.Update(dt);
	map.Update();
	blinky.Update(dt);

	inky.Update(dt);
	pinky.Update(dt);
	clyde.Update(dt);
}

void Game::UpdateSfmlEvents()
{
	
	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if (event.type == sf::Event::Closed)
			window.close();
	}

}

void Game::Render()
{

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