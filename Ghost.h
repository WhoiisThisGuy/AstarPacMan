#pragma once
#include <SFML/Graphics.hpp>
#define BLINKYSTARTPOSITIONX 5
#define BLINKYSTARTPOSITIONY 3
#include "Map.h"

class Ghost
{

public:

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

protected:

	void BackToBase();

private:

	virtual void findPath() = 0;
};

