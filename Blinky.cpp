#include "Blinky.h"

Blinky::Blinky(sf::Texture* GhostTexture,float speedf) {

	speed = speedf;
	tempDirection.x = 1;
	tempDirection.y = 0;
	GhostBody.setTexture(GhostTexture);
	GhostBody.setSize(sf::Vector2f(40.0f,40.0f));
	GhostBody.setPosition(sf::Vector2f(BLINKYSTARTPOSITIONX * CELLSIZE, BLINKYSTARTPOSITIONY * CELLSIZE));
	GhostBody.setOrigin(20.0f, 20.0f);

}

void Blinky::Update(float dt)
{
	
}

void Blinky::Draw(sf::RenderWindow& window)
{

	window.draw(GhostBody);

}

void Blinky::findPath()
{
}
