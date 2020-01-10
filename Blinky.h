#pragma once
#include "GhostEntity.h"
class Blinky : public GhostEntity
{
public:
	Blinky(sf::Texture* texture, float speed);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	
	void AstarSearch();

};

