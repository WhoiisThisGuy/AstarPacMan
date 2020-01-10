#include "Game.h"
#include <fstream>


//int ScreenWidth = sf::VideoMode::getDesktopMode().width;
//int ScreenHeight = sf::VideoMode::getDesktopMode().height;

Game::Game()
	: window(sf::VideoMode(Videomode),"PacmanAstar",sf::Style::Close | sf::Style::Titlebar),
	dt(0.0)
{
	font.loadFromFile("consola.ttf");
	PacManPosText.setFont(font);
	PacManPosText.setPosition(1100.0f,650.0f);
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
	map.Update(pacman->getUPosition());
	pacman->Update(dt,window,map);
	std::stringstream st;
	st << "Pacman pozicioja: (X,Y): " << pacman->getPosition().x / CellSizeDef << " " << pacman->getPosition().y / CellSizeDef;// CellSizeDef
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