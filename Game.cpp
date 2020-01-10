#include "Game.h"
#include <fstream>

#define PacmanMovementSpeed 100.0f
#define Videomode 1280.0f, 720.0f

Game::Game()
	: window(sf::VideoMode(Videomode), "Pacman"),
	dt(0.0)
{
	font.loadFromFile("consola.ttf");
	PacManPosText.setFont(font);
	PacManPosText.setPosition(800.0f,650.0f);
	PacManPosText.setFillColor(sf::Color::White);
	PacManPosText.setCharacterSize(20);
	PacmanTexture.loadFromFile("Pacman.png");
	pacman = new Pacman(window, &PacmanTexture, sf::Vector2u(2,4), PacmanMovementSpeed);
	window.setFramerateLimit(200);
}

Game::~Game() {

	delete pacman;
}

void Game::run()
{

	while (window.isOpen())
	{
		Update();
		Render();
	}

}

void Game::UpdateDt() //Állapot frissites
{
	//Update: mennyi idõ alatt frissít egy képkockát így más teljesitményû pc-n is ugyanannyi idõvel mozog a unit
	dt = deltaClock.restart().asSeconds();

}

void Game::Update()
{
	UpdateDt();
	UpdateSfmlEvents();
	pacman->Update(dt,window);
	std::stringstream st;
	st << "Pacman pozicioja: (X,Y): " << pacman->getPosition().x / 50 << " " << pacman->getPosition().y / 50;
	PacManPosText.setString(st.str());
}

void Game::UpdateSfmlEvents()
{

	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if (event.type == sf::Event::Closed)
			window.close();
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //kell ? kesobb megnezni
		//	Restart();
	}

}

void Game::Render() //Rajzolas
{

	window.clear();
	map.DrawMap(window);
	pacman->Draw(window);
	window.draw(PacManPosText);
	window.display();

}

//void Game::Restart() {
//
//	
//	GameOver = false;
//}