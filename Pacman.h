#pragma once
#include "Animation.h"
#include "Map.h"

#define PACMANSIZEX 30.0f
#define PACMANSIZEY 30.0f
#define PACMANSPEED 250.0f
#define STARTPOSX 1
#define STARTPOSY 1
#define STARTDIRECTION 1,0

#define OFFSET PACMANSIZEX/2 // This is needed to look further in front of pacmans direction. Used in canPacBufferedMove().

class Pacman
{

public:
	Pacman(sf::Texture* PacmanTexture, sf::Vector2u imageCount);

	void Draw(sf::RenderWindow& window);
	void Update(float dTime, sf::RenderWindow& window);

	sf::RectangleShape GetBody() { return this->body; };

	sf::RectangleShape body;

	sf::Vector2f getPosition() const { return body.getPosition(); };
	sf::Vector2u getUPosition() const;

	bool canPacMove(sf::Vector2f movement, sf::Vector2i& Direction) const; /* Collision detection */

	bool canPacBufferedMove(sf::Vector2i& Direction) const; /* Collision detection */

private:

	float speed;
	std::string health;
	unsigned int row;
	Animation animation;
	sf::Vector2i tempDirection;
	sf::Vector2i bufferedDirection;
	
};

