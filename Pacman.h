#pragma once
#include "Animation.h"

class Pacman
{

public:
	Pacman(sf::RenderWindow& window, sf::Texture* PacmanTexture, sf::Vector2u imageCount, float speed);


	void Draw(sf::RenderWindow& window);
	void Update(float dTime, sf::RenderWindow& window);

	//Collider GetCollider() { return Collider(body); }

	sf::RectangleShape GetBody() { return this->body; };

	sf::RectangleShape body;

	sf::Vector2f getPosition() const { return body.getPosition(); };
private:
	
	float speed;
	std::string health;
	unsigned int row;
	Animation animation;
	sf::Vector2i direction;
};

