#pragma once
#include "SFML/Graphics.hpp"
#include "Astar.h"
#include "Ghost.h"


class Blinky:public Ghost
{

public:

	Blinky(sf::Texture* texture, float speedf);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	
	void findPath();
	sf::RectangleShape GhostBody;
	sf::Vector2i tempDirection;
	float speed;
};

