#pragma once
#include "SFML\Graphics.hpp"
#include "LevelVariables.h"

#ifndef H_FRUIT
#define H_FRUIT

#define FRUITX 337
#define FRUITY 515
#define FRUITSIZE 35

using namespace sf;

class Fruit
{
public:
	enum fruitState{Active,Eaten,NotActive};
	Fruit();
	void Update();
	void Draw(RenderWindow& window);
	void setFruitTexture(unsigned short int&);
	bool checkCollision(FloatRect);
	void eaten();
	void activate(unsigned short int);
private:

private:
	fruitState state;
	Texture fruitTexture;
	RectangleShape fruitShape;
	unsigned short int fruitNum; //0-7 means the different fruits
	IntRect pictureSizes[8] = { {0,0,12,12},{13,0,11,12},{24,0,12,12},{36,0,12,12},{48,0,11,14},{59,0,11,12},{70,0,12,13},{82,0,7,14} };  //{left,top,with,height}
	Text scoreText;
	Clock fruitClock;
};

#endif