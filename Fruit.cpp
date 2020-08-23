#include "Fruit.h"
#include <string>

using namespace std;

Fruit::Fruit()
{
	//Initialization


	//Texture and shape
	fruitTexture.loadFromFile("Textures/Fruits.png");
	
	fruitShape.setTexture(&fruitTexture);
	//fruitShape.setFillColor(Color::Yellow);
	fruitShape.setSize(Vector2f(FRUITSIZE, FRUITSIZE));
	fruitShape.setOrigin(FRUITSIZE / 2, FRUITSIZE / 2);
	fruitShape.setPosition(Vector2f(FRUITX,FRUITY));

	//Text properties
	scoreText.setFont(font);
	scoreText.setFillColor(Color(252,181,255));
	scoreText.setCharacterSize(23);
	scoreText.setOrigin(FRUITSIZE / 2, FRUITSIZE / 2);
	scoreText.setPosition(Vector2f(FRUITX, FRUITY));
	//state
	
	state = NotActive;
	
}

void Fruit::Update()
{

	if (state == Active) {
		if (fruitClock.getElapsedTime().asSeconds() > 10) {
			state = NotActive;
		}
	}
	else if (state == Eaten) {
		if (fruitClock.getElapsedTime().asSeconds() > 4) {
			state = NotActive;
			scoreText.setString("");
		}
	}

}

void Fruit::Draw(RenderWindow& window)
{
	if (state == Active) {
		window.draw(fruitShape);
	}
	else if (state == Eaten ) {
		window.draw(scoreText);
	}
}

void Fruit::setFruitTexture(unsigned short int& fruitNum_)
{
	fruitNum = fruitNum_;
	
	fruitShape.setTextureRect(pictureSizes[fruitNum]);
}

bool Fruit::checkCollision(FloatRect pacmanIntRect)
{
	return state == Active ? fruitShape.getGlobalBounds().intersects(pacmanIntRect) : false;
}

void Fruit::eaten()
{
	if (state != Eaten) {
		state = Eaten;
		fruitClock.restart().asSeconds();
		scoreText.setString(to_string(levelValues[LEVELNUMBER][1]));
	}
}

void Fruit::activate(unsigned short int fruitNumber)
{
	if (state != Active) {
		setFruitTexture(fruitNumber);
		state = Active;
		fruitClock.restart().asSeconds();
	}
}

void Fruit::deactivate()
{
	state = NotActive;
}
