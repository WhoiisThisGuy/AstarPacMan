#pragma once
#include "Animation.h"
#include "Map.h"

#define PacmanSizeX 35.0f
#define PacmanSizeY 35.0f

#define pacmanstartcell 15,12

class Pacman
{

public:
	Pacman(sf::RenderWindow& window, sf::Texture* PacmanTexture, sf::Vector2u imageCount, float speed);


	void Draw(sf::RenderWindow& window);
	void Update(float dTime, sf::RenderWindow& window, Map& map);

	//Collider GetCollider() { return Collider(body); }

	sf::RectangleShape GetBody() { return this->body; };

	sf::RectangleShape body;

	sf::Vector2f getPosition() const { return body.getPosition(); };
	sf::Vector2u getUPosition() const;

	bool canPacMove(sf::Vector2f& movement,Map& map);

	void pushBack();

private:
	float speed;
	std::string health;
	unsigned int row;
	Animation animation;
	sf::Vector2i direction;
};

