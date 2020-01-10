#pragma once
#include "SFML\Graphics.hpp"

class GhostEntity
{

public:
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

protected:
	float speed;
	sf::RectangleShape GhostBody;

	sf::Clock spawnTimer;
private:

	virtual void AstarSearch() = 0;

};

