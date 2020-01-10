#include "Blinky.h"

Blinky::Blinky(sf::Texture* GhostTexture,float speed) {

	GhostBody.setTexture(GhostTexture);
}

void Blinky::Update(float dt)
{

	if()

}

void Blinky::Draw(sf::RenderWindow& window)
{

	window.draw(GhostBody);

}

void Blinky::AstarSearch()
{



}
