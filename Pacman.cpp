#include "Pacman.h"
#include <iostream>
#include <Windows.h>

Pacman::Pacman(sf::RenderWindow& window,sf::Texture* PacmanTexture, sf::Vector2u imageCount, float speed)
	: animation(PacmanTexture, imageCount)
{
	this->speed = speed;
	row = 1;
	direction.x = -1;
	direction.y = 0;
	body.setSize(sf::Vector2f(50.0f, 50.0f));
	body.setPosition(0.0f,0.0f);
	body.setTexture(PacmanTexture);
}

void Pacman::Draw(sf::RenderWindow& window)
{

	window.draw(body);

}

void Pacman::Update(float dTime, sf::RenderWindow& window)
{
	sf::Vector2f movement(0.0f, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && body.getPosition().y > 0){
			//movement.y -= speed * dTime;
			direction.y = -1;
			direction.x = 0;
			row = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && body.getPosition().y < window.getSize().y - 75) {
			//movement.y += speed * dTime;
			direction.y = 1;
			direction.x = 0;
			row = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && body.getPosition().x > 0) {
			//movement.x -= speed * dTime;
			row = 1;
			direction.x = -1;
			direction.y = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && body.getPosition().x < window.getSize().x - 75) {
			//movement.x += speed * dTime;
			direction.x = 1;
			direction.y = 0;
			row = 0;
		}
	movement.x += speed * dTime*direction.x;
	movement.y += speed * dTime * direction.y;
	animation.Update(row, dTime, 0.30f);
	//system("cls");
	//std::cout << body.getPosition().x/100 << " " << body.getPosition().y /100;
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}



//bool Pacman::fruitCollisionCheck(Fruits& fruit)
//{
//	float RectX, RectY, RectWidth, RectHeight, NearestX, NearestY, DeltaX, DeltaY, CircleX, CircleY;
//
//	CircleX = fruit.getFruitShape().getPosition().x;
//	CircleY = fruit.getFruitShape().getPosition().y;
//
//	RectX = head->getPacmanHeadShape().getGlobalBounds().left;
//	RectY = head->getPacmanHeadShape().getGlobalBounds().top;
//
//	RectWidth = head->getPacmanHeadShape().getGlobalBounds().width;
//	RectHeight = head->getPacmanHeadShape().getGlobalBounds().height;
//
//	NearestX = std::max(RectX, std::min(CircleX, RectX + RectWidth));
//	NearestY = std::max(RectY, std::min(CircleY, RectY + RectHeight));
//
//	DeltaX = CircleX - NearestX;
//	DeltaY = CircleY - NearestY;
//
//
//	if ((DeltaX * DeltaX + DeltaY * DeltaY) < (fruit.getRadius() * fruit.getRadius())) {
//
//		return true;
//	}
//
//	return false;
//
//
//}