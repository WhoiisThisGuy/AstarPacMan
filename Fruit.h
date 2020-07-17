#pragma once
#include "SFML\Graphics.hpp"

#ifndef H_FRUIT
#define H_FRUIT

using namespace sf;

class Fruit
{
public:
	Fruit();
	void Update(RenderWindow& window);
private:
	Texture fruitTexture;

	/* Constant variables */
	const uint16_t levelVariableColumn =123;
};

#endif