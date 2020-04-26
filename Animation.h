#include "SFML\Graphics.hpp"

#ifndef ANIM_H
#define ANIM_H

class Animation
{

public:
	Animation(sf::Texture texture,sf::Vector2u imageCount);

	void Update(int row, float deltaTime, float switchTime);
	void Update(int row, int column);

public:
	sf::IntRect uvRect;
	
private:
	sf::Vector2u AimageCount;
	sf::Vector2u currentImage;

	float totalTime;
};
#endif