#include "Menu.h"
#include "Playing.h"

Menu::Menu() : play(false),quit(false),  menuElemPlay(0, &menuElemQuit, &menuElemQuit), menuElemQuit(1, &menuElemPlay, &menuElemPlay){
	cout << "Menu consted" << endl;
	font.loadFromFile("arial.ttf");
	menuElemPlay.text.setFont(font);
	menuElemPlay.text.setString("Play");
	menuElemPlay.text.setFillColor(Color::White);
	menuElemPlay.text.setOutlineColor(Color::Green);
	menuElemPlay.text.setOutlineThickness(3);
	menuElemPlay.text.setCharacterSize(24);
	menuElemPlay.text.setPosition(300,200);

	menuElemQuit.text.setFont(font);
	menuElemQuit.text.setString("Quit");
	menuElemQuit.text.setFillColor(Color::White);
	menuElemQuit.text.setOutlineColor(Color::Green);
	menuElemQuit.text.setCharacterSize(24);
	menuElemQuit.text.setPosition(300, 500);

	temp = &menuElemPlay;
}

Menu::~Menu()
{
	cout << "Menu deleted"<<endl;
}



GameState* Menu::Update(RenderWindow& window)
{
	while (window.pollEvent(event))
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

			temp->text.setOutlineThickness(0);
			temp = temp->next;

			temp->text.setOutlineThickness(30);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			temp->text.setOutlineThickness(0);
			temp = temp->previous;

			temp->text.setOutlineThickness(30);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { // 2 many if's Q_Q
			if (temp->num == 0)
				return new Playing();
			else {
				window.close();
				return NULL;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			return NULL;
			}
		if (event.type == sf::Event::Closed) {
			window.close();
			return NULL;
		}
	}
	
	if(window.isOpen())
		Render(window);

	return NULL;
}

void Menu::Render(RenderWindow& window) {

	window.clear();
	window.draw(menuElemQuit.text);
	window.draw(menuElemPlay.text);
	window.display();
}

void Menu::EventsUpdate(GameState* tempstate, RenderWindow& window)
{
	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

			temp->text.setOutlineThickness(0);
			temp = temp->next;
			
			temp->text.setOutlineThickness(30);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			temp->text.setOutlineThickness(0);
			temp = temp->previous;
			
			temp->text.setOutlineThickness(30);
			

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			switch (temp->num)
			{
			case 0:
				delete tempstate;
				tempstate = new Playing();
				return;
			case 1:
				window.close();
				return;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		if (event.type == sf::Event::Closed)
			window.close();
	}
}
